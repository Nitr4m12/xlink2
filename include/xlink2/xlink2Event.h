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
public:
    Event();
    virtual ~Event();

    void initialize(u32);
    virtual void initializeImpl_();

    void finalize();
    virtual void doFinalize_();

    void destroyAllContainerAndAssetExecutor_();
    virtual void callEventCreateCallback_();
    virtual void callEventDestroyCallback_();

    void reEmit();
    void kill();

    u64 createRootContainer(UserInstance*, ResAssetCallTable const&);
    u8 calc();

    s32 getAliveAssetNum();
    s32 getFadeBySystemListAssetNum();

    void setOverwriteParam(TriggerType, ResTriggerOverwriteParam*, BoneMtx);

    void fade(int);
    void killOneTimeEvent();
    void fadeBySystem();

    virtual void fixDelayParam_();

    UserInstance* getUserInstance() const { return mUserInstance; }

    u32& get3() { return _3; }
    TriggerType& getTriggerType() { return mTriggerType; }

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