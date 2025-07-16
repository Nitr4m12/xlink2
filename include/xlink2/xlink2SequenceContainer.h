#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class SequenceContainer : ContainerBase {
public:
    ~SequenceContainer() override;

    CalcResult calc() override;

    bool callNextChildSequence_();

    bool start() override;

    bool callChildSequence_(s32);

private:
    s32 mSequenceIndex;
};
}  // namespace xlink2