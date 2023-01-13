#pragma once

#include "basis/seadTypes.h"
#include "heap/seadHeap.h"
#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2TriggerCtrlParam.h"
#include "xlink2/xlink2TriggerType.h"

namespace xlink2 {
class TriggerCtrlMgr {
public:
    TriggerCtrlMgr();

    s32 initialize(s32, s32, sead::Heap*);

    void allocAndSetupCtrlParam(ResMode, sead::Heap*);
    void calc();
    void changeAction(char const*, s32, s32);
    void changeAction(s32, s32, s32);
    void destroy();
    void freeCtrlParam(TriggerCtrlParam*);

    u64 getCurrentActionFrame(s32) const;
    u64 getCurrentActionName(s32) const;
    u64 getCurrentResActionIdx(s32) const;
    u64 getOverwriteBoneMtx(TriggerType, s32) const;
    u64 getUserInstance() const;

    bool isCurrentActionNeedToObserve(s32) const;

    void notifyActive();
    void postChangeResource(){};

    void reset();
    void resetAllModelTriggerConnection();

    void setActionFrame(s32, s32);
    void stopAction(s32);

    void updateActionNeedToCalcFlag(s32);
    void updateGlobalPropertyTriggerCtrl();

private:
    u32 _0;
    TriggerCtrlParam* mParam1;
    TriggerCtrlParam* mParam2;
    u32 _1;
};
}  // namespace xlink2