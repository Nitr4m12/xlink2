#pragma once

#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ResAssetCallTable.h"

namespace xlink2 {
class Event;
class ContainerBase {
    virtual ~ContainerBase();

public:
    ContainerBase();

    void* createChildContainer(ResAssetCallTable const&, ContainerBase);
    void destroy();
    void fade(int);
    void fadeBySystem();

    void initialize(Event*, ResAssetCallTable const&);

    void kill();
    void* killOneTimeEvent();

protected:
    ResAssetCallTable* mResAssetCallTable;
    Event* mEvent;
    void* _0;
    void* _1;
    s32 mResAssetDuration;
};
}  // namespace xlink2