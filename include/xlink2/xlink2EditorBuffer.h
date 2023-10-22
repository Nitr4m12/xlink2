#pragma once

#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2EditorResourceParam.h"

namespace xlink2 {
class System;
class ParamDefineTable;

class EditorBuffer {
public:
    EditorBuffer(System*, sead::Heap*);
    virtual ~EditorBuffer();

    void destroy();

    void allocReceiveBuffer(u32);

    void readFinished();

    void setupParamDefineTable(u8*, u32);

    void applyGlobalPropertyDefinition();

    EditorResourceParam* searchEditorResourceParam(sead::SafeString const&);

    ParamDefineTable* getParamDefineTable() const { return mParamDefineTable; }

private:
    System* mSystem;
    sead::Heap* mHeap;
    sead::SafeArray<EditorResourceParam*, 2> mParams;
    u32 _2;
    u32 _3;
    char* _4;
    u32 _5;
    sead::BufferedSafeString* _6;
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
    sead::FixedSafeString<64>* _18;
};
}  // namespace xlink2