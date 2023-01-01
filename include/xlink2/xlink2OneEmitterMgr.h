#pragma once

#include "math/seadVectorFwd.h"
#include "xlink2/xlink2OneEmitterInstance.h"
#include "xlink2/xlink2OneEmitterInstanceHandle.h"

namespace xlink2 {
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
}  // namespace xlink2