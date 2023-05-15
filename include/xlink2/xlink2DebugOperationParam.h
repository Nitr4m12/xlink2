#pragma once

#include <basis/seadTypes.h>

class DebugOperationParam {
public:
    // size = 0x358
    DebugOperationParam() = default;

    u8* get0() { return _0; }

private:
    u8 _0[0x358];
};