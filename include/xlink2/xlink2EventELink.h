#pragma once

#include "gfx/seadColor.h"

#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2UserInstanceELink.h"

namespace xlink2 {
class AssetExecutorELink;

class EventELink : Event {
public:
    ~EventELink() override;

    struct DelayEmitParam {
        sead::Color4f color;
        sead::Vector3f position;
        sead::Vector3f scale;
        sead::Matrix34f matrix34f;
        void* _4;
        u32 _5;
        f32 emissionIntervalScale;
        u8 _0x68[24];
        f32 directionalVel;
        u8 _0x84[44];
        sead::Color4f color0;
        sead::Color4f color1;
        u8 _0xd0[8];
        u32 _0xd8;
        s32 _0xdc;
        bool _0xe0;
        s32 particleCount;
        sead::BitFlag32 flag1;
        sead::BitFlag32 flag2;
        u8 _0xf0;
        void* _0xf8;

    };
    static_assert(sizeof(DelayEmitParam) == 0x100, "'xlink2::EventELink::DelayEmitParam' size mismatch");

    void callEventCreateCallback_() override;
    void callEventDestroyCallback_() override;

    void initializeImpl_() override;
    void doFinalize_() override;

    void fixDelayParam_() override;

    s32 getMtxSetType();

    void setManualParticleEmission(bool);
    void setManualParticleEmissionWithParticleCount(int);

    void emitParticle(sead::Vector3f&);
    AssetExecutorELink* getAliveAssetExecutor() const;

    UserInstanceELink* getUserInstanceELink() const { return static_cast<UserInstanceELink*>(mpUserInstance); }

private:
    DelayEmitParam mDelayEmitParam;
};
static_assert(sizeof(EventELink) == 0x198, "xlink2::EventELink size mismatch");

}  // namespace xlink2