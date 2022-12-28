#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
class ResProperty {
    u32 watchPropertyNamePos;
    u32 isGlobal;
    u32 triggerStartIdx;
    u32 triggerEndIdx;
};
}