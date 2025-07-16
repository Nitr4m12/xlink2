#include "xlink2/xlink2AlwaysTriggerCtrl.h"

#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2UserResource.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
AlwaysTriggerCtrl::AlwaysTriggerCtrl(UserInstance* user_instance,
                                     sead::Buffer<ModelTriggerConnection>* buffer) {
    mUserInstance = user_instance;
    mIsActive = true;
    mConnectionBuffer = buffer;
};

void AlwaysTriggerCtrl::calc()
{
    UserResource* user_resource {mUserInstance->getUserResource()};
    UserResourceParam* user_resource_param {user_resource->getParamWithSetupCheck()};

    if (user_resource_param != nullptr) {
        const ResUserHeader* user_header {user_resource->getUserHeader()};

        for (s32 i {0}; i < user_header->numResAlwaysTrigger; ++i) {
            ResAlwaysTrigger* always_trigger_table {user_resource_param->userBinParam.pResAlwaysTriggerTable};
            if (!mIsActive) {
                auto* asset_ctb {calcOffset<ResAssetCallTable>(always_trigger_table[i].assetCtbPos)};
                ResourceAccessor* accessor {user_resource->getAccessor()};
                if (!accessor->isNeedObserve(*asset_ctb))
                    continue;
            }

            ModelTriggerConnection* connection {getModelTriggerConnection_(i)};

            Event* event {connection->handle.getEvent()};
            if (event != nullptr && event->getCreateId() != connection->handle.getCreateId()) {
                ResAlwaysTrigger* always_trigger {user_resource->getAlwaysTriggerTableItem(i)};
                auto* asset_ctb {calcOffset<ResAssetCallTable>(always_trigger->assetCtbPos)};
                emitByTriggerImpl_(TriggerType::Always, i, always_trigger->overwriteParamPos, asset_ctb);
            }
        }
    }
}

void AlwaysTriggerCtrl::emitByTrigger_(s32 param1) {
    ResAlwaysTrigger* always_trigger {mUserInstance->getUser()->getUserResource()->getAlwaysTriggerTableItem(param1)};
    ResAssetCallTable* call_table {calcOffset<ResAssetCallTable>(always_trigger->assetCtbPos)};
    emitByTriggerImpl_(TriggerType::Always, param1, always_trigger->overwriteParamPos, call_table);
}

void AlwaysTriggerCtrl::notifyActive() {
    mIsActive = true;
}

AlwaysTriggerCtrl::~AlwaysTriggerCtrl() = default;

}  // namespace xlink2