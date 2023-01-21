#pragma once

#include <container/seadSafeArray.h>

#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ResAssetCallTable.h"

namespace xlink2 {
class Event;
class ContainerBase {
public:
    ContainerBase();
    virtual ~ContainerBase();

    virtual void initialize(Event*, ResAssetCallTable const&);
    virtual void destroy();
    virtual bool start() = 0;
    virtual u32 calc() = 0;
    virtual void fadeBySystem();
    virtual void fade(int);
    virtual void kill();
    virtual void* killOneTimeEvent();

    void* createChildContainer(ResAssetCallTable const&, ContainerBase*);

protected:
    ResAssetCallTable* mResAssetCallTable;
    Event* mEvent;
    sead::SafeArray<ContainerBase*, 2> mChildContainers;
    s32 mResAssetDuration;
};
}  // namespace xlink2