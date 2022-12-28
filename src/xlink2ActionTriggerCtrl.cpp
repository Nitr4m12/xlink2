#include "xlink2/xlink2ActionTriggerCtrl.h"

namespace xlink2 {

ActionTriggerCtrl::ActionTriggerCtrl(UserInstance* param_1,
                                     sead::Buffer<ModelTriggerConnection>* param_2,
                                     ResActionSlot* param_3)
{
    mBuffer = param_2;
    mUserInstance = param_1;
    mResActionSlot = param_3;
    _0 = 0;
    _1 = 0;
    _2 = 0;
    _3 = 0;
}

void ActionTriggerCtrl::reset() {
    _2 = 0;
    _0 = 0;
    _1 = 0;
    _3 = 0;
}
}  // namespace xlink2