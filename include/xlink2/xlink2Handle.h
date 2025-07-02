#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {
class Handle {
public:
    void* get0() { return mpResource; }
    int get8() { return mCreateId; }

private:
    void* mpResource = nullptr;
    u32 mCreateId = 0;
};
}  // namespace xlink2