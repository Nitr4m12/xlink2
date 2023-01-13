#pragma once

#include "math/seadVectorFwd.h"
#include "xlink2/xlink2Handle.h"

namespace xlink2 {
class OneEmitterInstance {
    virtual ~OneEmitterInstance();

public:
    void* initialize(char const*, u8);

    void emitParticle(sead::Vector3f const&, sead::Vector4f const&, sead::Vector2f const&);

    void release();

private:
    u8 _0;
    s32 _1;
    u32 _2;
    Handle* mHandle;
    void* _3;
    u8 _4;

    // 0x70
    // EmitReservationInfo* mEmitReservationInfo;
};
}  // namespace xlink2