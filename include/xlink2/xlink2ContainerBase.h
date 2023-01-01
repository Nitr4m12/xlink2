#pragma once

#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ResAssetCallTable.h"
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
    ResAssetCallTable* mResAssetCallTable;
    Event* mEvent;
    ContainerBase* mChildContainer;
    void* _0;
    s32 mResAssetDuration;
};
}