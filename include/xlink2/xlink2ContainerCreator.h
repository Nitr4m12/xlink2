#pragma once

#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ResAssetCallTable.h"

namespace xlink2::ContainerCreator {
ContainerBase* CreateContainer(Event*, ResAssetCallTable const&);
}