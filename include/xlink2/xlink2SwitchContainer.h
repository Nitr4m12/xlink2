#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ContainerBase.h"
#include "xlink2/xlink2ResAssetCallTable.h"

namespace xlink2 {
class SwitchContainer : ContainerBase {
     ~SwitchContainer() override;

public:
    u32 calc();
    u64 getConditionMatchChildTable();
    void printChildSelect(ResAssetCallTable const* /*unused*/) const{};
    bool start();
    bool start(ResAssetCallTable const*);

private:
};
}  // namespace xlink2