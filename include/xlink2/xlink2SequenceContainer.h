#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class SequenceContainer : ContainerBase {
public:
    ~SequenceContainer() override;

    u32 calc() override;

    u64 callNextChildSequence_();

    bool start() override;

    bool callChildSequence_(s32);

private:
    s32 _0;
};
}  // namespace xlink2