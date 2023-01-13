#include "xlink2/xlink2TriggerCtrlMgr.h"

namespace xlink2 {
TriggerCtrlMgr::TriggerCtrlMgr() {
    _0 = 0;
    _1 = 0;
    mParam1 = nullptr;
    mParam2 = nullptr;
}

u64 TriggerCtrlMgr::getCurrentActionFrame(s32 p1) const {
    p1 = 0xffffffff;
    return 0xffffffff;
}

u64 TriggerCtrlMgr::getCurrentActionName(s32 p1) const {
    p1 = 0;
    return 0;
}

}  // namespace xlink2