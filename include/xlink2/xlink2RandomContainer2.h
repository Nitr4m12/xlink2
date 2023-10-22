#pragma once


#include "xlink2/xlink2RandomContainer.h"
namespace xlink2 {
class RandomContainer2 : RandomContainer {

public:
    ~RandomContainer2() override;

    bool start() override;
};
}  // namespace xlink2