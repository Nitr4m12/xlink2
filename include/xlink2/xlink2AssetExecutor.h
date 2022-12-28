#pragma once

#include <math/seadMatrix.h>

#include <xlink2/xlink2.h>
#include <xlink2/xlink2EventELink.h>
#include "prim/seadBitFlag.h"

namespace xlink2 {
class AssetExecutor {
    virtual ~AssetExecutor();

public:
    void dumpDebugPrint();
    void onDestroy();
};

class AssetExecutorELink {
    virtual ~AssetExecutorELink();
public:
    void _applyColorAlpha();
    void _callEffectDeletedCallback();
    void activateImpl();
    bool calc();
    void calcMtx(sead::Matrix34f* param_1, ResAssetCallTable* param_2,
                 UserInstanceELink* param_3, ResTriggerOverwriteParam* param_4, BoneMtx param_5);

    void dumpDebugPrint();

    u32 emitEffect();
    void emitParticle(sead::Vector3f*);
    void fade();
    void fadeBySystem();
    void getResourceAccessor_() const;
    bool isAssetValid() const;
    u32 isLoopEvent() const;
    u8 isRequestReEmit() const;

    void kill();
    void onFinalize();
    void onResetOverwriteParam();
    void requestReEmit(bool);
    void restartCalcDraw();

    void setDelayParam(EventELink::DelayEmitParam*, sead::BitFlag32);
    void setInnerParam();
    void setInnerParamBit(ELinkAssetParamId, ELinkEventParam);
    void setManualParticleEmission(bool);
    void setManualParticleEmissionWithParticleCount(int);
    void setMtx(sead::Matrix34f const&, sead::Vector3f const&);
    void setPos(sead::Vector3f const&, sead::Vector3f const&);

    void stopCalcDraw();
    void updateParam();

private:
    // offset 0x20
    // ResourceAccessor* mResourceAccessor;

    // offset 0x28
    // ResAssetCallTable mResAssetCallTable;

    // offset 0x50
    // AssetExecutorELink mAssetExecutorELink

    // offset 0x60
    // EmitterSet? mEmitterSet?

    // offset 0x74-0x88
    // u32 mU32[6];

    // offset 0x8c
    // DelayEmitParam mDelayEmitParam;

    // offset 0x90
    // DelayEmitParam mDelayEmitParam2;

    // offset 0x94
    // DelayEmitParam mDelayEmitParam3;
};
}  // namespace xlink2