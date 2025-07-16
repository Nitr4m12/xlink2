#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class SwitchContainer : ContainerBase {
public:
    ~SwitchContainer() override;

    CalcResult calc() override;

    const ResAssetCallTable* getConditionMatchChildCallTable_();

    bool start_(const ResAssetCallTable*);

    bool start() override;

    void printChildSelect(const ResAssetCallTable* /*unused*/) const;
};
}  // namespace xlink2