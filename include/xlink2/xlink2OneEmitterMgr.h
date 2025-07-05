#pragma once

#include <gfx/seadTextWriter.h>

#include "xlink2/xlink2OneEmitterInstance.h"
#include "xlink2/xlink2OneEmitterInstanceHandle.h"

namespace xlink2 {
class OneEmitterMgr {
public:
    void* createOneEmitterInstance(const char*, u8);
    void* searchOneEmitterInstanceHandle(const char*);

    s32 createOneEmitterInstanceImpl(const char*, u8);
    
    void releaseOneEmitterInstance(const char*);

    OneEmitterInstance* getOneEmitterInstance(OneEmitterInstanceHandle);
    OneEmitterMgr* getFreeOneEmitterInstance();

    void drawDebugInformation(sead::TextWriter*);

private:
};
}  // namespace xlink2