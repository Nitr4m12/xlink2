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
    ResUserHeader* pResUserHeader2;
    s32 unknownNum;

};
}  // namespace xlink2