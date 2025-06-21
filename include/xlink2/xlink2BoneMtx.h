#pragma once

#include "math/seadMatrix.h"

namespace xlink2 {
struct BoneMtx {
    const sead::Matrix34f* rawMtx;
    u8 _0;
};
}  // namespace xlink2