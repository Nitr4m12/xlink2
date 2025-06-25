#pragma once

#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class RandomContainer : ContainerBase {
public:
    ~RandomContainer() override;

    s8 calc() override;
    bool start() override;
};
}  // namespace xlink2