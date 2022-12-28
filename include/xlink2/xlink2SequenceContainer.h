#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
class SequenceContainer {
    virtual ~SequenceContainer();

public:
    u32 calc();
    bool callChildSequence(s32);
    u64 callNextChildSequence();
    u64 start();

private:
};
}  // namespace xlink2