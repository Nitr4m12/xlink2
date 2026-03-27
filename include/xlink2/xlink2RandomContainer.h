#pragma once

#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class RandomContainer : public ContainerBase {
public:
    ~RandomContainer() override;

    bool calc() override;
    bool start() override;
};

class RandomContainer2 : public RandomContainer {
public:
    using CallbackFunc = xlink2::ContainerBase*(*)(UserInstance*, ResAssetCallTable*); 

    static CallbackFunc sRandomContainerCallbackFunc;

    ~RandomContainer2() override;

    bool start() override;
};
}  // namespace xlink2