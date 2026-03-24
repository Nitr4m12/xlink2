#pragma once

#include <math/seadMatrix.h>

namespace xlink2 {
struct BoneMtx {
    BoneMtx() = default;

    void reset()
    {
        rawMtx = &sead::Matrix34f::ident;
        _0 = 0;
    }

    const sead::Matrix34f* getMatrix34fRawPtr() { return rawMtx; }

    void setRawMtx(const sead::Matrix34f* mtx, u8 unknown) { rawMtx = mtx; _0 = unknown; }
    bool isNullMtxPtr() { return rawMtx == nullptr; }

    const sead::Matrix34f* rawMtx {&sead::Matrix34f::ident};
    u8 _0{};
};
}  // namespace xlink2