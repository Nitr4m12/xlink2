#pragma once

#include "gfx/seadColor.h"

#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2UserInstanceELink.h"

namespace xlink2 {
class EventELink : Event {
public:
    ~EventELink() override;

    struct DelayEmitParam {
        sead::Color4f mColor;
        sead::Vector3f vectorPos;
        sead::Vector3f vector;
        sead::Matrix34f matrix34f;
        u64 _4;
        u32 _5;
        f32 _6;
    };

    void callEventCreateCallback_() override;
    void callEventDestroyCallback_() override;

    void initializeImpl_() override;
    void doFinalize_() override;

    void fixDelayParam_() override;

    u64 getMtxSetType();

    void setManualParticleEmission(bool);
    void setManualParticleEmissionWithParticleCount(int);

    void emitParticle();
    u64 getAliveAssetExecutor() const;

    UserInstanceELink* getUserInstanceELink() const { return static_cast<UserInstanceELink*>(mpUserInstance); }

private:
    DelayEmitParam mDelayEmitParam;
    u8 _100[120];
    bool mIsEmitting;
    s32 mParticleCount;
    sead::BitFlag32 mFlag1;
    sead::BitFlag32 mFlag2;
    void* _16;
    void* _17;
};
static_assert(sizeof(EventELink) == 0x198, "xlink2::EventELink size mismatch");

}  // namespace xlink2