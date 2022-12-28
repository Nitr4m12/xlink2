#include "xlink2/xlink2ActionTriggerCtrl.h"

namespace xlink2 {

// NON_MATCHING?: two sub intructions reordered
ActionTriggerCtrl::ActionTriggerCtrl(UserInstance* param_1, sead::Buffer<ModelTriggerConnection>* param_2, ResActionSlot* param_3) {
    _0 = 0;
    mBuffer = param_2;
    mResActionSlot = param_3;
    mUserInstance = param_1;
    _1 = 0;
    _2 = 0;
    // ptr = nullptr;
};
}