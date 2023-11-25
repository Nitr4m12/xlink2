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

    virtual bool initialize(Event*, ResAssetCallTable const&);
    virtual void destroy();
    virtual void start() = 0;
    virtual u32 calc() = 0;
    virtual void fadeBySystem();
    virtual void fade(int);
    virtual void kill();
    virtual bool killOneTimeEvent();

    void* createChildContainer_(ResAssetCallTable const&, ContainerBase*);

protected:
    ResAssetCallTable* mResAssetCallTable;
    Event* mEvent;
    ContainerBase* mChild;
    ContainerBase* mParent;
    s32 mAssetDuration;
};
}  // namespace xlink2