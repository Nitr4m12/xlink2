#pragma once

#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class RandomContainer2 : ContainerBase {
    ~RandomContainer2() override;

public:
    void* start();

private:
};
}  // namespace xlink2