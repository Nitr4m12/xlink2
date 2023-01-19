#pragma once

#include "xlink2/xlink2CommonResourceParam.h"
namespace xlink2 {
struct UserResourceParam : public CommonResourceParam {
    // size=0xb0
    u32 _0;
    void* _1;
    u32 _2;
    void* _3;
    void* _4;
    void* _5;
    bool setup;
};
}  // namespace xlink2