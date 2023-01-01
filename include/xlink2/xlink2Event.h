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
    void initializeImpl();

    u8 calc();
    void callEventCreateCallback();
    void callEventDestroyCallback();

    u64 createRootContainer(UserInstance*, ResAssetCallTable const&);
    void destroyAllContainerAndAssetExecutor();

    void doFinalize();
    void fade(int);
    void fadeBySystem();
    void finalize();
    void fixDelayParam();

    s32 getAliveAssetNum();
    s32 getFadeBySystemListAssetNum();

    void kill();
    void killOneTimeEvent();
    void reEmit();

    void setOverwriteParam(TriggerType, ResTriggerOverwriteParam*, BoneMtx);

private:
    // 0x28
    UserInstance* mUserInstance;
    ResAssetCallTable* mResAssetCallTable;
    TriggerType mTriggerType;
    ResTriggerOverwriteParam mResTriggerOverwriteParam;
    BoneMtx* mBoneMtx;
};
}  // namespace xlink2