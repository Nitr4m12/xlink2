#include "xlink2/xlink2ActionTriggerCtrl.h"

namespace xlink2 {

// NON-MATCHING: Two subroutines in the wrong order
ActionTriggerCtrl::ActionTriggerCtrl(UserInstance* param_1,
                                     sead::Buffer<ModelTriggerConnection>* param_2,
                                     ResActionSlot* param_3)
{
    _1 = 0;
    mUserInstance = param_1;
    _2 = 0;
    mBuffer = param_2;
    mResActionSlot = param_3;
    mResAction = nullptr;
    _3 = 0;
}

void ActionTriggerCtrl::reset() {
    _2 = 0;
    _1 = 0;
    _3 = 0;
}
}  // namespace xlink2