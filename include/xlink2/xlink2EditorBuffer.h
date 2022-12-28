#pragma once

#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>
#include "xlink2/xlink2System.h"


namespace xlink2 {
class EditorBuffer {
    virtual ~EditorBuffer();
public:
    EditorBuffer(System*, sead::Heap*);
    void allocReceiveBuffer(u32);
    void applyGlobalPropertyDefinition();
    void destroy();
    void readFinished();

    void* searchEditorResourceParam(sead::SafeString const&);
    void setupParamDefineTable(u8*, u32);
private:
};
}