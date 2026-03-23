#include "xlink2/xlink2TriggerCtrl.h"

#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2Handle.h"
#include "xlink2/xlink2IUser.h"
#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2TriggerLocator.h"
#include "xlink2/xlink2UserResource.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
// NON-MATCHING: TriggerLocator constructor not inlining properly
void TriggerCtrl::emitByTriggerImpl_(TriggerType trigger_type, s32 idx, 
                                     u32 overwrite_param_pos, const ResAssetCallTable* asset_ctb)
{
    if (asset_ctb != nullptr) {
        auto* connection {mConnectionBuffer->get(idx)};
        setBoneMatrixToConnection_(overwrite_param_pos, connection);

        auto* param {solveOffset<ResTriggerOverwriteParam>(overwrite_param_pos)};
        TriggerLocator locator {*asset_ctb, trigger_type, param, connection->rootMtx};
        mUserInstance->emitImpl(locator, &connection->handle);
    }
}

void TriggerCtrl::fadeByTrigger_(s32 idx) 
{
    constexpr const char* TRIGGERTYPES[3] {"Action", "Property", "Always"};

    Handle* handle {&mConnectionBuffer->get(idx)->handle};
    Event* event {handle->getEvent()};
    if (event != nullptr && event->getCreateId() == handle->getCreateId()) {
        mUserInstance->printLogFadeOrKill(event, "fadeBySystem by %s Trigger", TRIGGERTYPES[(s32)event->getTriggerType()]);
        event->fadeBySystem();
        handle->reset();
    }
}

ModelTriggerConnection* TriggerCtrl::getModelTriggerConnection_(s32 idx)
{
    if (mConnectionBuffer != nullptr && mConnectionBuffer->getSize() > idx)
        return mConnectionBuffer->get(idx);
    
    return nullptr;
}

// NON-MATCHING
void TriggerCtrl::resetIsOnceCheck_() 
{
    for (s32 i {0}; i < mConnectionBuffer->size(); ++i)
        mConnectionBuffer->get(i)->isActive = false;
}

void TriggerCtrl::setBoneMatrixToConnection_(u32 overwrite_param_pos, ModelTriggerConnection* connection)
{
    auto& accessor {mUserInstance->getUser()->getUserResource()->getAccessor()};
    if (accessor.isBoneNameOverwritten(overwrite_param_pos)) {
        const char* bone_overwrite_name {accessor.getOverwriteBoneName(overwrite_param_pos)};
        if (*bone_overwrite_name == '\0') {
            connection->rootMtx = mUserInstance->getRootMtx();
        }
        else {
            auto* bone_world_mtx {mUserInstance->getIUser()->getBoneWorldMtxPtr(bone_overwrite_name)};
            connection->rootMtx.rawMtx = bone_world_mtx;
            connection->rootMtx._0 = 1;
            if (bone_world_mtx == nullptr)
                connection->rootMtx = mUserInstance->getRootMtx();
        }
    }

}
}  // namespace xlink2