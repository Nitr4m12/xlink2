#pragma once

#include "xlink2/xlink2ContainerBase.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2ResourceUtil.h"

namespace xlink2 {
class BlendContainer : ContainerBase {
    ~BlendContainer() override;

public:
    u32 calc() override;
    u8 callAllChildContainer();
    void initialize(Event*, ResAssetCallTable const&) override;
    bool start() override;

private:
};
}  // namespace xlink2