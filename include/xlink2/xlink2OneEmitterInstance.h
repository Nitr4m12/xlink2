#pragma once

#include <math/seadVectorFwd.h>

namespace xlink2 {
class Handle;

class OneEmitterInstance {
public:
    virtual ~OneEmitterInstance();
    
    void* initialize(const char*, u8);

    void emitParticle(const sead::Vector3f&, const sead::Vector4f&, const sead::Vector2f&);

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