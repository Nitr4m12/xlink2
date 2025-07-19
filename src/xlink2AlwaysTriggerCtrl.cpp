#include "xlink2/xlink2AlwaysTriggerCtrl.h"

#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2UserResource.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
AlwaysTriggerCtrl::AlwaysTriggerCtrl(UserInstance* user_instance,
                                     sead::Buffer<ModelTriggerConnection>* buffer) 
{
    mUserInstance = user_instance;
    mIsActive = true;
    mConnectionBuffer = buffer;
};

AlwaysTriggerCtrl::~AlwaysTriggerCtrl() = default;

void AlwaysTriggerCtrl::calc()
{
    UserResource* user_resource {mUserInstance->getUserResource()};
    UserResourceParam* user_resource_param {user_resource->getParamWithSetupCheck()};

    if (user_resource_param != nullptr) {
        ResAlwaysTrigger* always_trigger_table {user_resource_param->userBinParam.pResAlwaysTriggerTable};
        const ResUserHeader* user_header {user_resource->getUserHeader()};
        s32 num_always_trigger {static_cast<s32>(user_header->numResAlwaysTrigger)};

        for (s32 i {0}; i < num_always_trigger; ++i) {
            auto* asset_ctb {calcOffset<ResAssetCallTable>(always_trigger_table[i].assetCtbPos)};
            if (!mIsActive) {
                ResourceAccessor* accessor {user_resource->getAccessor()};
                if (!accessor->isNeedObserve(*asset_ctb))
                    continue;
            }

            ModelTriggerConnection* connection {getModelTriggerConnection_(i)};
            Event* event {connection->handle.getEvent()};
            if (event == nullptr || event->getCreateId() != connection->handle.getCreateId()) {
                emitByTrigger_(i);
            }
        }
        mIsActive = false;
    }
}

void AlwaysTriggerCtrl::emitByTrigger_(s32 idx) 
{
    ResAlwaysTrigger* always_trigger {mUserInstance->getUser()->getUserResource()->getAlwaysTriggerTableItem(idx)};
    ResAssetCallTable* call_table {calcOffset<ResAssetCallTable>(always_trigger->assetCtbPos)};
    emitByTriggerImpl_(TriggerType::Always, idx, always_trigger->overwriteParamPos, call_table);
}

void AlwaysTriggerCtrl::notifyActive() 
{
    mIsActive = true;
}
}  // namespace xlink2