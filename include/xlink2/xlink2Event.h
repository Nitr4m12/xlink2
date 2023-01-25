#pragma once

#include <container/seadSafeArray.h>

#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResTriggerOverwriteParam.h"
#include "xlink2/xlink2TriggerType.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class ContainerBase;
class UserInstance;

class Event {
    virtual ~Event();

public:
    Event();
    void initialize(u32);
    virtual void initializeImpl_();

    u8 calc();
    virtual void callEventCreateCallback_();
    virtual void callEventDestroyCallback_();

    u64 createRootContainer(UserInstance*, ResAssetCallTable const&);
    void destroyAllContainerAndAssetExecutor();

    virtual void doFinalize_();
    void fade(int);
    void fadeBySystem();
    void finalize();
    virtual void fixDelayParam_();

    s32 getAliveAssetNum();
    s32 getFadeBySystemListAssetNum();

    void kill();
    void killOneTimeEvent();
    void reEmit();

    void setOverwriteParam(TriggerType, ResTriggerOverwriteParam*, BoneMtx);

private:
    u32 _0;
    void* _1;
    void* _2;
    u32 _3;
    UserInstance* mUserInstance;
    ResAssetCallTable* mResAssetCallTable;
    TriggerType mTriggerType;
    ResTriggerOverwriteParam* mResTriggerOverwriteParam;
    BoneMtx* mBoneMtx;
    u8 _4;
    ContainerBase* mRootContainer;
    void* _5;
    void* _6;
    u32 _7;
    u32 _8;
    sead::SafeArray<AssetExecutor*, 2> mAssetExecutors;
    u32 _9;
    u32 _10;
    u32 _11;
    u8 _12;
};
}  // namespace xlink2