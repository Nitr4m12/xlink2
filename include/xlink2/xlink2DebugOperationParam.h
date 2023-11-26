#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

class DebugOperationParam {
public:
    DebugOperationParam() = default;

    u32 get0() const { return _0; }
    u32 get258() const { return _0x258; }

private:
    //u8 _0[0x358];
    u32 _0;
    float _0x08;
    float _0x0c;
    void* _0x10;
    void* _0x18;
    sead::FixedSafeString<64> _0x20;
    sead::FixedSafeString<64> _0x78;
    sead::FixedSafeString<64> _0xd0;
    sead::FixedSafeString<128> _0x128;
    sead::FixedSafeString<128> _0x1c0;
    u32 _0x258;
    sead::FixedSafeString<64> _0x260;
    u32 _0x2b8;
    u16 _0x2bc;
    sead::FixedSafeString<128> _0x2c0;
};