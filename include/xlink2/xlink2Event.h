#pragma once

#include <container/seadPtrArray.h>
#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResTriggerOverwriteParam.h"
#include "xlink2/xlink2TriggerType.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class UserInstance;

class Event {
    virtual ~Event();

public:
    Event();
    void initialize(u32);
    virtual void initializeImpl_(){};

    u8 calc();
    virtual void callEventCreateCallback_(){};
    virtual void callEventDestroyCallback_(){};

    u64 createRootContainer(UserInstance*, ResAssetCallTable const&);
    void destroyAllContainerAndAssetExecutor();

    virtual void doFinalize_(){};
    void fade(int);
    void fadeBySystem();
    void finalize();
    void fixDelayParam_(){};

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
    void* _5;
    u64 _6;
    u64 _7;
    u32 _8;
    u32 _9;
    void* _10;
    void* _11;
    u32 _12;
    u32 _13;
    u32 _14;
    u8 _15;
};
}  // namespace xlink2