#pragma once

#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class RandomContainer : ContainerBase {
public:
    ~RandomContainer() override;

    u32 calc() override;
    bool start() override;
};
}  // namespace xlink2