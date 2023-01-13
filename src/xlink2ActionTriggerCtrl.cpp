#include "xlink2/xlink2ActionTriggerCtrl.h"

namespace xlink2 {

// NON-MATCHING: Two subroutines in the wrong order
ActionTriggerCtrl::ActionTriggerCtrl(UserInstance* param_1,
                                     sead::Buffer<ModelTriggerConnection>* param_2,
                                     ResActionSlot* param_3)
    : _0{nullptr}, mResActionSlot{param_3} {
    mBuffer = param_2;
    mUserInstance = param_1;
    _1 = 0;
    mResAction = nullptr;
    _2 = 0;
}

// TODO
// u32 ActionTriggerCtrl::getActionTriggerType_(ResActionTrigger const& action_trigger)
// {
//     u32 v1 {3};
//     u32 v2 {2};
//     u16 flag {action_trigger.flag};

//     if ((flag & 0x10) != 0) {
//         v1 = 0;
//     }

//     if ((flag & 8) != 0) {
//         v2 = v1;
//     }

//     v2 = 1;
//     if ((flag & 4) != 0) {
//         v1 = v2;
//     }

//     return v1;
// }

void ActionTriggerCtrl::reset() {
    mResAction = nullptr;
    _0 = nullptr;
    _1 = 0;
    _2 = 0;
}
}  // namespace xlink2