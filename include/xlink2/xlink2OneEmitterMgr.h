#pragma once

#include "math/seadVectorFwd.h"
#include "xlink2/xlink2.h"

namespace xlink2 {
class OneEmitterInstance;
class OneEmitterInstanceHandle;
class OneEmitterMgr {
public:
    void* createOneEmitterInstance(char const*, u8);
    s32 createOneEmitterInstanceImpl(char const*, u8);
    // void drawDebugInformation(sead::TextWriter);

    OneEmitterMgr* getFreeOneEmitterInstance();
    OneEmitterInstance* getOneEmitterInstance(OneEmitterInstanceHandle);

    void releaseOneEmitterInstance(char const*);

    void* searchOneEmitterInstanceHandle(char const*);

private:
};

class OneEmitterInstance {
public:
    void* initialize(char const*, u8);

    void emitParticle(sead::Vector3f const&, sead::Vector4f const&, sead::Vector2f const&);

    void release();
private:
};
}  // namespace xlink2