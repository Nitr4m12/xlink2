#pragma once

#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class RandomContainer : ContainerBase {
    ~RandomContainer() override;

public:
    void calc();
    bool start();

private:
};
}  // namespace xlink2