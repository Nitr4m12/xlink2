#pragma once

#include "prim/seadSafeString.h"
#include "xlink2/xlink2CommonResourceParam.h"
#include "xlink2/xlink2EditorHeader.h"
#include "xlink2/xlink2ResUserHeader.h"

namespace xlink2 {
struct EditorResourceParam : CommonResourceParam {
    EditorHeader* pEditorHeader;
    u32 _0;
    ResUserHeader* pResUserHeader;
    sead::SafeString* editorName;
    sead::SafeString* editorName2;
    s32 unknownNum;
    u32 _1;
    u64 _2;
    u64 _3;
    u64 _4;
    u64 _5;
    u64 _6;
    u64 _7;
    u64 _8;
    u64 _9;
    u64 _10;
    u64 _11;
    u64 _12;

};
static_assert(sizeof(EditorResourceParam) == 0x100, "Wrong size for 'xlink2::EditorResourceParam'");

}  // namespace xlink2