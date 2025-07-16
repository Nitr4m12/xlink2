#pragma once

#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2ELinkAssetParamId.h"
#include "xlink2/xlink2ELinkEventParam.h"
#include "xlink2/xlink2EventELink.h"

namespace xlink2 {
class HandleELink;
class ResourceAccessorELink;

class UserInstanceELink;

class AssetExecutorELink : AssetExecutor {
public:
    ~AssetExecutorELink() override;

    u32 calc() override;

    u32 emitEffect();

    ResourceAccessorELink* getResourceAccessor_() const;

    void stopCalcDraw();
    void restartCalcDraw();

    void updateParam();

    bool isLoopEvent() const override;

    void kill() override;

    void _callEffectDeletedCallback();

    void setDelayParam(EventELink::DelayEmitParam*, sead::BitFlag32);

    void fade(s32) override;
    void fadeBySystem() override;

    void activateImpl_() override;

    void setInnerParam_();

    void setMtx_(const sead::Matrix34f&, const sead::Vector3f&);
    void setPos_(const sead::Vector3f&, const sead::Vector3f&);

    void calcMtx(sead::Matrix34f*, ResAssetCallTable*, UserInstanceELink*,
                 ResTriggerOverwriteParam*, BoneMtx);

    void _applyColorAlpha();

    void onResetOverwriteParam_() override;

    void setManualParticleEmission(bool);
    void setManualParticleEmissionWithParticleCount(int);

    void emitParticle(sead::Vector3f*);

    void dumpDebugPrint() override;

    f32 setInnerParamBit_(ELinkAssetParamId, ELinkEventParam);

    bool isAssetValid() const override;

    void requestReEmit(bool) override;
    bool isRequestReEmit() const override;

    void onFinalize_() override;

private:
    u8 _5;
    u32 mDelay;
    void* _7;
    HandleELink* mHandle;
    u32 _9;
    u32 _16;
    u16 _10;
    u16 _11;
    sead::Vector3f mPosition;
    sead::Vector3f mRotation;
    f32 _12;
    f32 _13;
    f32 _14;
    f32 _15;
};
static_assert(sizeof(AssetExecutorELink) == 0xa0, "Wrong size of 'xlink2::AssetExecutorELink'");
}  // namespace xlink2