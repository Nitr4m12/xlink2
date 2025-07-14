#pragma once

#include "basis/seadTypes.h"

#include "xlink2/xlink2Event.h"

namespace xlink2 {
class EventELink : Event {
public:
    ~EventELink() override;

    struct DelayEmitParam {
        f32 _0;
        f32 _1;
        f32 _2;
        f32 _3;
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

private:
    DelayEmitParam mDelayEmitParam;
    u8 unknown[120];
    bool _13;
    s32 _14;
    void* _15;
    void* _16;
    void* _17;
};
static_assert(sizeof(EventELink) == 0x198, "xlink2::EventELink size mismatch");

}  // namespace xlink2