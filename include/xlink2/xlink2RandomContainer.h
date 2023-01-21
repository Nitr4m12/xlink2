#pragma once

#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class RandomContainer : ContainerBase {
    ~RandomContainer() override;

public:
    u32 calc() override;
    bool start() override;

private:
};
}  // namespace xlink2