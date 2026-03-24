#pragma once

#include <prim/seadSafeString.h>
#include <prim/seadBitFlag.h>
#include <math/seadVector.h>

namespace xlink2 {
class DebugOperationParam {
public:
    DebugOperationParam();

    sead::BitFlag32 getDebugUserFlag() const { return mDebugUserFlag; }
    sead::BitFlag32 getPrintFlag() const { return mPrintFlag; }
    bool getPrintFlagCheck() const { return mPrintFlag & 1; }

    const sead::FixedSafeString<64>& getDebugStringAction() const { return mDebugStringAction; }
    const sead::FixedSafeString<64>& getDebugStringLocalProperty() const { return mDebugLocalStringProperty; }
    const sead::FixedSafeString<128>& getDebugStringEvent() const { return mDebugStringEvent; }

private:
    sead::BitFlag32 mDebugUserFlag;
    f32 mAxisScale;
    f32 mTextScale;
    sead::Vector2f mCharacterDisplayOffsetUser;
    sead::Vector2f mCharacterDisplayOffsetSystem;
    sead::FixedSafeString<64> mDebugStringUser;
    sead::FixedSafeString<64> mDebugStringAction;
    sead::FixedSafeString<64> mDebugLocalStringProperty;
    sead::FixedSafeString<128> mDebugStringEvent;
    sead::FixedSafeString<128> mKeyName;
    sead::BitFlag32 mPrintFlag;
    sead::FixedSafeString<64> mDebugStringGlobalProperty;
    f32 mFixedGlobalProperty;
    bool mBreakWhenEmit;
    bool mBreakTargetOnly;
    sead::FixedSafeString<128> mDebugKeyName;

};
static_assert(sizeof(DebugOperationParam) == 0x358, "xlink2::DebugOperationParam size mismatch");
} // namespace xlink2