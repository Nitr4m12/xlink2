#pragma once

#include <container/seadSafeArray.h>

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
    virtual bool start() = 0;
    virtual u32 calc() = 0;
    virtual void fadeBySystem();
    virtual void fade(int);
    virtual void kill();
    virtual bool killOneTimeEvent();

    ContainerBase* createChildContainer_(const ResAssetCallTable&, ContainerBase*);

protected:
    ResAssetCallTable* mpAssetCallTable;
    Event* mpEvent;
    ContainerBase* mpChild;
    ContainerBase* mpParent;
    s32 mAssetDuration;
};
}  // namespace xlink2
