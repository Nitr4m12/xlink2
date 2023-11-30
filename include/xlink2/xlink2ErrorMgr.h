#pragma once

#include "xlink2/xlink2Error.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2User.h"

namespace sead {
class TextWriter;
}

namespace xlink2 {
class User;
class ErrorMgr {

public:
    explicit ErrorMgr(System const*);
    virtual ~ErrorMgr();

    void add(Error::Type, User const*, char const*);
    void clear(User const*);
    void clearAll();
    void calc();

    void draw(sead::TextWriter*) const;

    bool shouldErrorNoticed_(Error const*);
    bool shouldErrorNoticed_(Error::Type const*);

    void* getIsDebugBreakEnablePtr();

private:
    u32 _0;
    u8 _1[0x5100];
    // 0x288
    // u32 _1;

    // 0x508
    // u32 _2;

    // 0x788
    // u32 _3;

    // 0xa08
    // u32 _4;

    // 0xc88
    // u32 _5;

    // 0xf08
    // u32 _6;

    // 0x1188
    // u32 _7;

    // 0x1408
    // u32 _8;

    // 0x1688
    // u32 _9;

    // 0x1908
    // u32 _10;

    // 0x1b88
    // u32 _11;

    // 0x1e08
    // u32 _12;

    // 0x2088
    // u32 _13;

    // 0x2308
    // u32 _14;

    // 0x2588
    // u32 _15;

    // 0x2808
    // u32 _16;

    // 0x2a88
    // u32 _17;

    // 0x2d08
    // u32 _18;

    // 0x2f88
    // u32 _19;

    // 0x3208
    // u32 _20;

    // 0x3488
    // u32 _21;

    // 0x3708
    // u32 _22;

    // 0x3988
    // u32 _23;

    // 0x3c08
    // u32 _24;

    // 0x3e88
    // u32 _25;

    // 0x4108
    // u32 _26;

    // 0x4388
    // u32 _27;

    // 0x4608
    // u32 _28;

    // 0x4888
    // u32 _29;

    // 0x4b08
    // u32 _30;

    // 0x4d88
    // u32 _31;

    // 0x5008
    // u32 _33;

    // 0x5010
    // void* _34;

    // 0x5018
    // System* _32;

    // 0x5020
    // u32 _36;

    // 0x5024
    // u32 _37;

    // 0x5028
    // u32 _38

    // 0x502c
    // u32 _39;

    // 0x5030
    // u32 _40;

    // 0x5034
    // u64 _41;

    // 0x503c
    // u64 _42;

    // 0x5044
    // u64 _43;

    // 0x504c
    // u64 _44;

    // 0x5054
    // u64 _41;

    // 0x505c
    // u64 _41;

    // 0x5064
    // u64 _41;

    // 0x506c
    // u64 _41;

    // 0x5074
    // u64 _41;

    // 0x507c
    // u64 _41;

    // 0x5084
    // u64 _41;

    // 0x508c
    // u64 _41;

    // 0x5094
    // u64 _41;

    // 0x509c
    // u64 _41;

    // 0x50a4
    // u64 _41;

    // 0x50ac
    // u64 _41;

    // 0x50b4
    // u64 _41;

    // 0x50bc
    // u64 _41;

    // 0x50c4
    // u32 _41;

    // 0x50c8
    // u32 _35;

    // 0x50d0
    // sead::CriticalSection* mCriticalSection
};
static_assert(sizeof(ErrorMgr) == 0x5110, "Wrong size for 'xlink2::ErrorMgr'");

}  // namespace xlink2