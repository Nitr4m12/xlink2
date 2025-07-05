#pragma once

#include "math/seadMatrix.h"

namespace xlink2 {
struct BoneMtx {
    BoneMtx() = default;

    BoneMtx(const BoneMtx& other) 
    {
        rawMtx = other.rawMtx;
        _0 = other._0;
    }

    void reset()
    {
        rawMtx = &sead::Matrix34f::ident;
        _0 = 0;
    }

    bool isNullMtxPtr() { return rawMtx == nullptr; }

    const sead::Matrix34f* rawMtx {&sead::Matrix34f::ident};
    u8 _0{};
};
}  // namespace xlink2