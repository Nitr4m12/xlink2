#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class SequenceContainer : ContainerBase {
    ~SequenceContainer() override;

public:
    u32 calc();
    bool callChildSequence(s32);
    u64 callNextChildSequence();
    u64 start();

private:
    s32 _0;
};
}  // namespace xlink2