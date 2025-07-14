#pragma once

#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

#include "xlink2/xlink2EditorResourceParam.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2System.h"

namespace xlink2 {
class System;
class ParamDefineTable;

class EditorBuffer {
public:
    EditorBuffer(System*, sead::Heap*);
    virtual ~EditorBuffer();

    void destroy();

    u8* allocReceiveBuffer(u32);

    void readFinished();

    void setupParamDefineTable(u8*, u32);

    void applyGlobalPropertyDefinition();

    EditorResourceParam* searchEditorResourceParam(const sead::SafeString&);

    ParamDefineTable* getParamDefineTable() const { return mParamDefineTable; }

private:
    System* mSystem{nullptr};
    sead::Heap* mHeap{nullptr};
    sead::OffsetList<xlink2::EditorResourceParam> mParams{};
    u8* mReceiveBuffer{nullptr};
    u32 mReceiveBufferSize{0};
    sead::FixedSafeString<64> _6{};
    ParamDefineTable* mParamDefineTable{nullptr};
    u8* mParamDefineBuffer{nullptr};
};
}  // namespace xlink2