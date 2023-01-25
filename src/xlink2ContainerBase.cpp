#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
ContainerBase::ContainerBase() {
    mResAssetDuration = 0;
    mChildContainers[0] = nullptr;
    mChildContainers[1] = nullptr;
    mResAssetCallTable = nullptr;
    mEvent = nullptr;
}
}  // namespace xlink2