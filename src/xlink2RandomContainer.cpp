#include "xlink2/xlink2RandomContainer.h"

namespace xlink2 {
RandomContainer::~RandomContainer() = default;

ContainerBase::CalcResult RandomContainer::calc()
{
    auto* child {mpChild};
    CalcResult result {child->calc()};
    if (result != CalcResult::Success) {
        mpChild = nullptr;
        child->destroy();
        return assetFinished();
    }
    return CalcResult(!result);
}

RandomContainer2::~RandomContainer2() = default;
}