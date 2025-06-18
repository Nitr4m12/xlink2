#pragma once

#include <container/seadSafeArray.h>
#include <container/seadOffsetList.h>

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

    void reEmit(const ResAssetCallTable*);
    void kill();

    bool createRootContainer(UserInstance*, const ResAssetCallTable&);
    u8 calc();

    s32 getAliveAssetNum() const;
    s32 getFadeBySystemListAssetNum() const;

    void setOverwriteParam(TriggerType, ResTriggerOverwriteParam*, BoneMtx);

    void fade(int);
    void killOneTimeEvent();
    void fadeBySystem();

    virtual void fixDelayParam_();

    UserInstance* getUserInstance() const { return mpUserInstance; }

    u32& get0x20() { return _0x20; }
    TriggerType& getTriggerType() { return mTriggerType; }

private:
    u32 _0x08{0};
    void* _0x10{nullptr};
    void* _0x18{nullptr};
    u32 _0x20{0};
    UserInstance* mpUserInstance;
    const ResAssetCallTable* mpAssetCallTable;
    TriggerType mTriggerType;
    ResTriggerOverwriteParam* mpTriggerOverwriteParam{nullptr};
    BoneMtx* mpBoneMtx{nullptr};
    bool _0x50{true};
    ContainerBase* mpRootContainer{nullptr};
    sead::OffsetList<xlink2::AssetExecutor> mAliveAssetExecutors;
    sead::OffsetList<xlink2::AssetExecutor> mFadeBySystemAssetExecutors;
    float _0x90;
    u8 mGroupId{0xff};
};
}  // namespace xlink2