#pragma once

#include "math/seadMatrix.h"
#include "prim/seadBitFlag.h"
#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2ELinkAssetParamId.h"
#include "xlink2/xlink2ELinkEventParam.h"
#include "xlink2/xlink2EventELink.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResTriggerOverwriteParam.h"
#include "xlink2/xlink2UserInstanceELink.h"

namespace xlink2 {
class UserInstanceELink;

class AssetExecutorELink : AssetExecutor {
    ~AssetExecutorELink() override;

public:
    void _applyColorAlpha();
    void _callEffectDeletedCallback();
    void activateImpl_() override;
    bool calc() override;
    void calcMtx(sead::Matrix34f* param_1, ResAssetCallTable* param_2, UserInstanceELink* param_3,
                 ResTriggerOverwriteParam* param_4, BoneMtx param_5);

    void dumpDebugPrint() override;

    u32 emitEffect();
    void emitParticle(sead::Vector3f*);
    void fade(s32) override;
    void fadeBySystem() override;
    ResourceAccessor* getResourceAccessor_() const;
    bool isAssetValid() const override;
    bool isLoopEvent() const override;
    bool isRequestReEmit() const override;

    void kill() override;
    void onFinalize_() override;
    void onResetOverwriteParam_() override;
    void requestReEmit(bool) override;
    void restartCalcDraw();

    void setDelayParam(EventELink::DelayEmitParam*, sead::BitFlag32);
    void setInnerParam_();
    u32 setInnerParamBit(ELinkAssetParamId, ELinkEventParam);
    void setManualParticleEmission(bool);
    void setManualParticleEmissionWithParticleCount(int);
    void setMtx(sead::Matrix34f const&, sead::Vector3f const&);
    void setPos(sead::Vector3f const&, sead::Vector3f const&);

    void stopCalcDraw();
    void updateParam();

private:
    void* _0;
    void* _1;
    EventELink* mEvent;
    UserInstanceELink* mUserInstance;
    ResAssetCallTable* mResAssetCallTable;
    u32 _2;
    f32 _3;
    ResTriggerOverwriteParam* mResTriggerOverwriteParam;
    BoneMtx* mBoneMtx;
    void* _4;
    u8 _5;
    u32 _6;
    void* _7;
    HandleELink* mHandle;
    void* _9;
    u16 _10;
    u16 _11;
    u32 mPositionX;
    u32 mPositionY;
    u32 mPositionZ;
    u32 mRotationX;
    u32 mRotationY;
    u32 mRotationZ;
    f32 _12;
    f32 _13;
    f32 _14;
    f32 _15;
};
}  // namespace xlink2