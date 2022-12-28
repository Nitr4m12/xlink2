#pragma once

#include "xlink2/xlink2.h"

namespace xlink2 {
class TriggerCtrlParam;
class TriggerCtrl {
public:
    void emitByTriggerImpl(TriggerType, s32, u32, ResAssetCallTable const*);
    void fadeByTrigger(s32);
    void* getModelTriggerConnection(s32);
    void resetIsOnceCheck();
    void setBoneMatrixToConnection(u32, ModelTriggerConnection*);

private:
};

class TriggerCtrlMgr {
    virtual ~TriggerCtrlMgr();

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
    void postChangeResource();

    void reset();
    void resetAllModelTriggerConnection();

    void setActionFrame(s32, s32);
    void stopAction(s32);

    void updateActionNeedToCalcFlag(s32);
    void updateGlobalPropertyTriggerCtrl();
    ;

private:
};
}  // namespace xlink2