#pragma once

#include <basis/seadTypes.h>
#include <heap/seadHeap.h>

#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2TriggerCtrlParam.h"
#include "xlink2/xlink2TriggerType.h"

namespace xlink2 {
class UserInstance;

class TriggerCtrlMgr {
public:
    TriggerCtrlMgr();
    ~TriggerCtrlMgr() = default;

    void destroy();
    void initialize(s32 /*unused*/, s32 /*unused*/, sead::Heap* /*unused*/);

    void freeCtrlParam_(TriggerCtrlParam*);

    void calc();
    void reset();

    void allocAndSetupCtrlParam(ResMode, sead::Heap*);

    const UserInstance* getUserInstance_() const;

    void postChangeResource(){};

    void changeAction(char const*, s32, s32);
    void updateActionNeedToCalcFlag(s32);
    void changeAction(s32, s32, s32);
    void setActionFrame(s32, s32);
    void stopAction(s32);
    bool isCurrentActionNeedToObserve(s32) const;
    u64 getCurrentResActionIdx(s32) const;

    void updateGlobalPropertyTriggerCtrl();

    void notifyActive();

    u64 getOverwriteBoneMtx(TriggerType, s32) const;

    u64 getCurrentActionName(s32) const;
    u64 getCurrentActionFrame(s32) const;

    void resetAllModelTriggerConnection();

    ResMode getResMode() { return mResMode; }
    void setResMode(ResMode mode) { mResMode = mode; }

    u32 get1() const { return _1; };

private:
    ResMode mResMode;
    sead::SafeArray<TriggerCtrlParam*, 2> mParams;
    u32 _1;
};
}  // namespace xlink2