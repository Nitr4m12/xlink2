#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class SequenceContainer : ContainerBase {
    ~SequenceContainer() override;

public:
    u32 calc() override;
    bool callChildSequence(s32);
    u64 callNextChildSequence();
    bool start() override;

private:
    s32 _0;
};
}  // namespace xlink2