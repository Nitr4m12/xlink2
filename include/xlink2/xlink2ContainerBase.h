#pragma once

#include <container/seadSafeArray.h>

#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
class Event;

class ContainerBase {
public:
    ContainerBase();
    virtual ~ContainerBase();

    enum CalcResult {
        Failure,
        Success,
    };

    virtual bool initialize(Event*, const ResAssetCallTable&);
    virtual void destroy();
    virtual bool start() = 0;
    virtual bool calc() = 0;
    virtual void fadeBySystem();
    virtual void fade(int);
    virtual void kill();
    virtual bool killOneTimeEvent();

    ContainerBase* createChildContainer_(const ResAssetCallTable&, ContainerBase*);

    // Doesn't seem to exist, but similar logic is used throughout containers, so it's here as a helper
    ContainerBase* createChildContainer(const ResAssetCallTable& asset_ctb, UserInstance* user_instance, ContainerBase* child) 
    {
        Event* event {mpEvent};

        const char* container_name {user_instance->getContainerTypeName(*mpAssetCallTable).cstr()};
        const char* key_name {solveOffset<char>(mpAssetCallTable->keyNamePos)};
        
        const char* container_child_name {user_instance->getContainerTypeName(asset_ctb).cstr()};
        const char* key_name_child {solveOffset<char>(asset_ctb.keyNamePos)};

        user_instance->printLogContainerSelect(*event, "%s[%s] -> %s[%s]", container_name, key_name, container_child_name, key_name_child);

        return createChildContainer_(asset_ctb, child);
    }

    ContainerBase* getNext() { return mpParent; }
    void setNext(ContainerBase* parent) { mpParent = parent; }

    bool assetFinished() 
    {
        if (mAssetDuration > 0)
            --mAssetDuration;
    
        if (mAssetDuration != 0) {
            return !start();
        }
        return true;
    }

protected:
    ResAssetCallTable* mpAssetCallTable;
    Event* mpEvent;
    ContainerBase* mpChild;
    ContainerBase* mpParent;
    s32 mAssetDuration;
};
}  // namespace xlink2
