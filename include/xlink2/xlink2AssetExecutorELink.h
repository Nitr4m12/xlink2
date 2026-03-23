#pragma once

#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2ELinkAssetParamId.h"
#include "xlink2/xlink2ELinkEventParam.h"
#include "xlink2/xlink2EventELink.h"
#include "xlink2/xlink2HandleELink.h"

namespace xlink2 {
class ResourceAccessorELink;

class UserInstanceELink;

class AssetExecutorELink : public AssetExecutor {
public:
    explicit AssetExecutorELink(Event* event) { mpEvent = event; }

    ~AssetExecutorELink() override;

    u32 calc() override;

    u32 emitEffect();

    const ResourceAccessorELink& getResourceAccessor_() const;

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

    void emitParticle(sead::Vector3f&);

    void dumpDebugPrint() override;

    f32 setInnerParamBit_(ELinkAssetParamId, ELinkEventParam);

    bool isAssetValid() const override;

    void requestReEmit(bool) override;
    bool isRequestReEmit() const override;

    void onFinalize_() override;

    UserInstanceELink* getUserInstanceELink() { return static_cast<UserInstanceELink*>(mpUserInstance); }
    EventELink* getEventELink() { return static_cast<EventELink*>(mpEvent); }

private:
    sead::BitFlag8 mBitFlag;
    u32 mDelay{};
    bool _0x58{};
    HandleELink mHandle{};
    sead::BitFlag16 mPositionFlag;
    sead::BitFlag16 mRotationFlag;
    sead::Vector3f mPosition;
    sead::Vector3f mRotation;
    sead::Color4f mColor;
};
static_assert(sizeof(AssetExecutorELink) == 0xa0, "'xlink2::AssetExecutorELink' size mismatch");
}  // namespace xlink2