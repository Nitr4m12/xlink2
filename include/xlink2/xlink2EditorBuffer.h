#pragma once

#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

#include "xlink2/xlink2System.h"
#include "xlink2/xlink2ParamDefineTable.h"

namespace xlink2 {
class System;
class ParamDefineTable;

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

    ParamDefineTable* getParamDefineTable() const { return mParamDefineTable; }

private:
    System* mSystem;
    sead::Heap* mHeap;
    void* _0;
    void* _1;
    u32 _2;
    u32 _3;
    char* _4;
    u32 _5;
    sead::SafeString* _6;
    void* _7;
    u32 _8;
    u32 _9;
    u64 _10;
    u64 _11;
    u64 _12;
    u64 _13;
    u64 _14;
    u64 _15;
    u64 _16;
    u64 _17;
    ParamDefineTable* mParamDefineTable;
    void* _18;
};
}  // namespace xlink2