#pragma once

#include "math/seadVectorFwd.h"

namespace xlink2 {
class OneEmitterInstance {
public:
    void* initialize(char const*, u8);

    void emitParticle(sead::Vector3f const&, sead::Vector4f const&, sead::Vector2f const&);

    void release();
private:
};
}