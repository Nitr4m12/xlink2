#pragma once

#include "xlink2/xlink2.h"

namespace xlink2 {
class SwitchContainer {
    virtual ~SwitchContainer();

public:
    u32 calc();
    u64 getConditionMatchChildTable();
    u64 printChildSelect(ResAssetCallTable const*) const;
    bool start();
    bool start(ResAssetCallTable const*);

private:
};
}  // namespace xlink2