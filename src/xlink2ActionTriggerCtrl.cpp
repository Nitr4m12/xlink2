#include "xlink2/xlink2ActionTriggerCtrl.h"

namespace xlink2 {

// NON-MATCHING: Two subroutines in the wrong order
ActionTriggerCtrl::ActionTriggerCtrl(UserInstance* param_1,
                                     sead::Buffer<ModelTriggerConnection>* param_2,
                                     ResActionSlot* param_3)
    :_0{nullptr}, mResActionSlot{param_3}
{
    mBuffer = param_2;
    mUserInstance = param_1;
    _1 = 0;
    mResAction = nullptr;
    _2 = 0;
}

void ActionTriggerCtrl::reset() {
    mResAction = nullptr;
    _0 = nullptr;
    _1 = 0;
    _2 = 0;
}
}  // namespace xlink2