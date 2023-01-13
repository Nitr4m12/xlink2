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
class AssetExecutorELink : AssetExecutor {
    ~AssetExecutorELink() override;

public:
    void _applyColorAlpha();
    void _callEffectDeletedCallback();
    void activateImpl();
    bool calc();
    void calcMtx(sead::Matrix34f* param_1, ResAssetCallTable* param_2, UserInstanceELink* param_3,
                 ResTriggerOverwriteParam* param_4, BoneMtx param_5);

    void dumpDebugPrint() override;

    u32 emitEffect();
    void emitParticle(sead::Vector3f*);
    void fade();
    void fadeBySystem();
    ResourceAccessor* getResourceAccessor_() const;
    bool isAssetValid() const;
    u32 isLoopEvent() const;
    u8 isRequestReEmit() const;

    void kill();
    void onFinalize_();
    void onResetOverwriteParam();
    void requestReEmit(bool);
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
    u32 mPositionXWithOverwrite;
    u32 mPositionYWithOverwrite;
    u32 mPositionZWithOverwrite;
    u32 mRotationXWithOverwrite;
    u32 mRotationYWithOverwrite;
    u32 mRotationZWithOverwrite;
    f32 _12;
    f32 _13;
    f32 _14;
    f32 _15;
};
}  // namespace xlink2