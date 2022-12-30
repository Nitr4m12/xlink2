#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ContainerType.h"

namespace xlink2 {
struct ResContainerParam {
    ContainerType type;
    s32 childrenStartIndex;
    s32 childrenEndIndex;
    u32 watchPropertyNamePos;
    s32 watchPropertyId;
    s16 localPropertyNameIdx;
    bool isGlobal;
};
}  // namespace xlink2