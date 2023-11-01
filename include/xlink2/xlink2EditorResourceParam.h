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
    sead::FixedSafeString<64> editorName;
    u32 _1;
    void* _2;
    void* _3;
};
static_assert(sizeof(EditorResourceParam) == 0x100, "Wrong size for 'xlink2::EditorResourceParam'");

}  // namespace xlink2