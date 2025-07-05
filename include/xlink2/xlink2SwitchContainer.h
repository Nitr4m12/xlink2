#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2ContainerBase.h"
#include "xlink2/xlink2ResAssetCallTable.h"

namespace xlink2 {
class SwitchContainer : ContainerBase {
public:
    ~SwitchContainer() override;

    CalcResult calc() override;

    const ResAssetCallTable* getConditionMatchChildCallTable_();

    bool start_(ResAssetCallTable const*);

    bool start() override;

    void printChildSelect(ResAssetCallTable const* /*unused*/) const;
};
}  // namespace xlink2