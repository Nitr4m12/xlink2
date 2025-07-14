#pragma once

#include "prim/seadSafeString.h"
#include "xlink2/xlink2CommonResourceParam.h"
#include "xlink2/xlink2ResUserHeader.h"

namespace xlink2 {
struct EditorResourceParam : CommonResourceParam {
    u8* binBuffer {};
    u32 binBufferSize {};
    ResUserHeader* pResUserHeader {};
    sead::FixedSafeString<64> editorName;
    bool isInitialized {false};
    void* _2 {};
    void* _3 {};

    void reset()
    {
        CommonResourceParam::reset();
        if (binBuffer != nullptr) {
            delete[] binBuffer;
            binBuffer = nullptr;
        }
        binBufferSize = 0;
        pResUserHeader = nullptr;
        editorName.clear();
        isInitialized = false;
    }
};
static_assert(sizeof(EditorResourceParam) == 0x100, "xlink2::EditorResourceParam size mismatch");

}  // namespace xlink2