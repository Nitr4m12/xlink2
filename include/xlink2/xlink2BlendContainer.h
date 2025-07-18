#pragma once

#include "xlink2/xlink2ContainerBase.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ResAssetCallTable.h"

namespace xlink2 {
class BlendContainer : ContainerBase {
public:
    ~BlendContainer() override;
    bool initialize(Event* event, const ResAssetCallTable&) override;
    bool start() override;

    bool callAllChildContainer_();

    CalcResult calc() override;
};
}  // namespace xlink2
