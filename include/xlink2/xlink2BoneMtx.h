#pragma once

#include "math/seadMatrix.h"

namespace xlink2 {
struct BoneMtx {
    const sead::Matrix34f* rawMtx {&sead::Matrix34f::ident};
    u8 _0{};

    BoneMtx() = default;

    BoneMtx(const BoneMtx& other) 
    {
        rawMtx = other.rawMtx;
        _0 = other._0;
    }
};
}  // namespace xlink2