#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
class EventELink {
    virtual ~EventELink();
public:
    class DelayEmitParam;
    void initializeImpl();

    void callEventCreateCallback();
    void callEventDestroyCallback();

    void doFinalize();
    void emitParticle();
    void fixDelayParam();

    u64 getAliveAssetExecutor() const;
    u64 getMtxSetType();

    void setManualParticleEmission(bool);
    void setManualParticleEmissionWithParticleCount(int);
};
}