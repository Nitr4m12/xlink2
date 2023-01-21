#pragma once


#include "xlink2/xlink2RandomContainer.h"
namespace xlink2 {
class RandomContainer2 : RandomContainer {
    ~RandomContainer2() override;

public:
    bool start() override;
};
}  // namespace xlink2