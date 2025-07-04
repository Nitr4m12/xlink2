#include "xlink2/xlink2AlwaysTriggerCtrl.h"

namespace xlink2 {
AlwaysTriggerCtrl::AlwaysTriggerCtrl(UserInstance* user_instance,
                                     sead::Buffer<ModelTriggerConnection>* buffer) {
    mUserInstance = user_instance;
    mIsActive = true;
    mConnectionBuffer = buffer;
};

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