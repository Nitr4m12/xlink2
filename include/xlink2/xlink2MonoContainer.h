#pragma once

#include "xlink2/xlink2.h"
#include "xlink2/xlink2Event.h"

namespace xlink2 {
class MonoContainer {
    virtual ~MonoContainer();
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
};
}  // namespace xlink2