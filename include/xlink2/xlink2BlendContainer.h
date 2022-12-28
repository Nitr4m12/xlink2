#pragma once

#include "xlink2/xlink2.h"
#include "xlink2/xlink2Event.h"

namespace xlink2 {
class ContainerBase {
    virtual ~ContainerBase();

public:
    ContainerBase() = default;

    void* createChildContainer(ResAssetCallTable const&, ContainerBase);
    void destroy();
    void fade(int);
    void fadeBySystem();

    void* initialize(Event*, ResAssetCallTable const&);

    void kill();
    void* killOneTimeEvent();

private:
};

class BlendContainer : ContainerBase {
    ~BlendContainer() override;

public:
    u32 calc();
    u8 callAllChildContainer();
    void* initialize(Event*, ResAssetCallTable const&);
    u8 start();

private:
    ResAssetCallTable* mResAssetCallTable;
    Event* mEvent;
};

void* CreateContainer(Event*, ResAssetCallTable const&);
}  // namespace xlink2