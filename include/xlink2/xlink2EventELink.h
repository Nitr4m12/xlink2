#pragma once

#include "basis/seadTypes.h"

#include "xlink2/xlink2Event.h"

namespace xlink2 {
class EventELink : Event {
    ~EventELink() override;

public:
    class DelayEmitParam;
    void initializeImpl_() override;

    void callEventCreateCallback_() override;
    void callEventDestroyCallback_() override;

    void doFinalize_() override;
    void emitParticle();
    void fixDelayParam();

    u64 getAliveAssetExecutor() const;
    u64 getMtxSetType();

    void setManualParticleEmission(bool);
    void setManualParticleEmissionWithParticleCount(int);

private:
    DelayEmitParam* mDelayEmitParam;

    // 0x178
    // bool

    // 0x17c
    // s32

    // 0x180
    // u32

    // 0x184
    // u32

    // 0x190
    // void*
};
}  // namespace xlink2