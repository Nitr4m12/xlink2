#pragma once

#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ResAssetCallTable.h"

namespace xlink2 {
class ContainerCreator {
public:
    static ContainerBase* CreateContainer(Event*, ResAssetCallTable const&);
};
}  // namespace xlink2