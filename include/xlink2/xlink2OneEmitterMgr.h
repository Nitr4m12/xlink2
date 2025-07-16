#pragma once

#include <gfx/seadTextWriter.h>

namespace xlink2 {
class OneEmitterInstance;
class OneEmitterInstanceHandle;

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