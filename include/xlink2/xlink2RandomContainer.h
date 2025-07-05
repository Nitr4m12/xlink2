#pragma once

#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class RandomContainer : ContainerBase {
public:
    ~RandomContainer() override;

    CalcResult calc() override;
    bool start() override;
};

class RandomContainer2 : public RandomContainer {
public:
    ~RandomContainer2() override;

    bool start() override;
};

}  // namespace xlink2