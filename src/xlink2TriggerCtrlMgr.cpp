#include "xlink2/xlink2TriggerCtrlMgr.h"

namespace xlink2 {
TriggerCtrlMgr::TriggerCtrlMgr() {
    _0 = 0;
    _1 = 0;
    mParams[0] = nullptr;
    mParams[1] = nullptr;
}

void TriggerCtrlMgr::initialize(s32 /*unused*/, s32 /*unused*/, sead::Heap* /*unused*/) {}

u64 TriggerCtrlMgr::getCurrentActionFrame(s32 p1) const {
    p1 = 0xffffffff;
    return 0xffffffff;
}

u64 TriggerCtrlMgr::getCurrentActionName(s32 p1) const {
    p1 = 0;
    return 0;
}

}  // namespace xlink2