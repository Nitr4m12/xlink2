#pragma once

#include "xlink2/xlink2ContainerBase.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ResAssetCallTable.h"

namespace xlink2 {
class MonoContainer : ContainerBase {
    ~MonoContainer() override;

public:
    u64 initialize(Event*, ResAssetCallTable);

    void* calc();
    void destroy();
    void fade(int);
    void fadeBySystem();

    void kill();
    s64 killOneTimeEvent();
    u64 start();

private:
    f32 _1;
    f32 _2;
    // TODO: possibly more?
};
}  // namespace xlink2