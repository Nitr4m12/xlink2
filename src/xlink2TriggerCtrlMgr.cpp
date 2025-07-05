#include <prim/seadPtrUtil.h>

#include "xlink2/xlink2TriggerCtrlMgr.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
TriggerCtrlMgr::TriggerCtrlMgr() {
    mResMode = ResMode::Editor;
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

const UserInstance* TriggerCtrlMgr::getUserInstance_() const
{
    return static_cast<UserInstance*>(sead::PtrUtil::addOffset(this, -offsetof(UserInstance, mTriggerCtrlMgr)));
}

}  // namespace xlink2