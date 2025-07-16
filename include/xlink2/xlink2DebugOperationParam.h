#pragma once

#include <prim/seadSafeString.h>
#include <prim/seadBitFlag.h>
#include <math/seadVector.h>

namespace xlink2 {
class DebugOperationParam {
public:
    DebugOperationParam();

    sead::BitFlag32 getDebugFlag() const { return mDebugFlag; }
    sead::BitFlag32 getPrintFlag() const { return mPrintFlag; }
    bool get258Check() const { return mPrintFlag & 1; }

private:
    sead::BitFlag32 mDebugFlag;
    f32 mAxisScale;
    f32 mTextScale;
    sead::Vector2f mCharacterDisplayOffsetUser;
    sead::Vector2f mCharacterDisplayOffsetSystem;
    sead::FixedSafeString<64> mDebugUser;
    sead::FixedSafeString<64> mDebugAction;
    sead::FixedSafeString<64> mDebugLocalProperty;
    sead::FixedSafeString<128> mDebugEvent;
    sead::FixedSafeString<128> mKeyName;
    sead::BitFlag32 mPrintFlag;
    sead::FixedSafeString<64> mDebugGlobalProperty;
    f32 mFixedGlobalProperty;
    bool mBreakWhenEmit;
    bool mBreakTargetOnly;
    sead::FixedSafeString<128> mDebugKeyName;

};
static_assert(sizeof(DebugOperationParam) == 0x358, "xlink2::DebugOperationParam size mismatch");
} // namespace xlink2