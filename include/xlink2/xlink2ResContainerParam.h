#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ContainerType.h"

namespace xlink2 {
class ResContainerParam {
    ContainerType type;
    u32 childrenStartIndex;
    u32 childrenEndIndex;
};
}  // namespace xlink2