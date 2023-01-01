#pragma once

#include <xlink2/xlink2Event.h>
#include "xlink2/xlink2ContainerBase.h"
#include "xlink2/xlink2ResAssetCallTable.h"

namespace xlink2 {
class BlendContainer : ContainerBase {
    ~BlendContainer() override;

public:
    u32 calc();
    u8 callAllChildContainer();
    void* initialize(Event*, ResAssetCallTable const&);
    u8 start();

private:
};
}  // namespace xlink2