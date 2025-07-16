#pragma once

#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class ContainerCreator {
public:
    static ContainerBase* CreateContainer(Event*, const ResAssetCallTable&);
};
}  // namespace xlink2