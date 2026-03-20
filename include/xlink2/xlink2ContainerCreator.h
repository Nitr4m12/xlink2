#pragma once

#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class ContainerCreator {
public:
    constexpr static u64 sContainerSizeMax = 0x38;

    static ContainerBase* CreateContainer(Event*, const ResAssetCallTable&);
};
}  // namespace xlink2