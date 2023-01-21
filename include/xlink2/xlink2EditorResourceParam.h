#pragma once

#include "prim/seadSafeString.h"
#include "xlink2/xlink2CommonResourceParam.h"
#include "xlink2/xlink2EditorHeader.h"
namespace xlink2 {
struct EditorResourceParam : CommonResourceParam {
    EditorHeader* pEditorHeader;
    u32 _0;
    ResUserHeader* pResUserHeader2;
    sead::SafeString* editorName;
    ResUserHeader* pResUserHeader3;
    s32 unknownNum;

};
}  // namespace xlink2