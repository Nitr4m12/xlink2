#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ContainerBase.h"
#include "xlink2/xlink2ResAssetCallTable.h"

namespace xlink2 {
class SequenceContainer : ContainerBase {
    virtual ~SequenceContainer();

public:
    u32 calc();
    bool callChildSequence(s32);
    u64 callNextChildSequence();
    u64 start();

private:
};
}  // namespace xlink2