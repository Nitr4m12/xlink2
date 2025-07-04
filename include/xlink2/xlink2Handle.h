#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {
class Handle {
public:
    void* get0() { return mpResource; }
    s32 getCreateId() { return mCreateId; }

    void reset()
    {
        mpResource = nullptr;
        mCreateId = 0;
    }

private:
    void* mpResource = nullptr;
    s32 mCreateId = 0;
};
}  // namespace xlink2