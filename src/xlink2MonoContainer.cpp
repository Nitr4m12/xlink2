#include "xlink2/xlink2MonoContainer.h"

#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2UserResource.h"

namespace xlink2 {
MonoContainer::~MonoContainer() = default;

bool MonoContainer::killOneTimeEvent()
{
    if (mpChild != nullptr && !mpChild->killOneTimeEvent()) {
        kill();
        return true;
    }
    return false;
}

void MonoContainer::kill()
{
    if (mpChild != nullptr) {
        auto* event {mpEvent};
        auto* child_executor {reinterpret_cast<AssetExecutor*>(mpChild)};
        mpChild = nullptr;
        event->getAliveAssetExecutors().erase(child_executor);
        event->getFadeBySystemExecutors().pushBack(child_executor);
        child_executor->kill();
    }

    mAssetDuration = 0;
    mOverwriteDuration = -1.0f;
}

void MonoContainer::fade(s32 i1)
{
    if (mpChild != nullptr) {
        auto* event {mpEvent};
        auto* child_executor {reinterpret_cast<AssetExecutor*>(mpChild)};
        mpChild = nullptr;
        event->getAliveAssetExecutors().erase(child_executor);
        event->getFadeBySystemExecutors().pushBack(child_executor);
        child_executor->fade(i1);
    }

    mAssetDuration = 0;
    mOverwriteDuration = -1.0f;
}

// NON-MATCHING
void MonoContainer::destroy()
{
    if (mpChild != nullptr) {
        auto* child_executor {reinterpret_cast<AssetExecutor*>(mpChild)};
        mpChild = nullptr;
        mpEvent->getAliveAssetExecutors().erase(child_executor);
        mpEvent->getUserInstance()->getUser()->getSystem()->freeAssetExecutor(child_executor);
    }
    auto* container_heap {mpEvent->getUserInstance()->getUser()->getSystem()->getContainerHeap()};
    MonoContainer::~MonoContainer();
    container_heap->free(this);
}

void MonoContainer::fadeBySystem()
{
    if (mpChild != nullptr) {
        auto* event {mpEvent};
        auto* child_executor {reinterpret_cast<AssetExecutor*>(mpChild)};
        mpChild = nullptr;
        event->getAliveAssetExecutors().erase(child_executor);
        event->getFadeBySystemExecutors().pushBack(child_executor);
        child_executor->fadeBySystem();
    }

    mAssetDuration = 0;
    mOverwriteDuration = -1.0f;
}

bool MonoContainer::initialize(Event* event, const ResAssetCallTable& asset_ctb)
{
    ContainerBase::initialize(event, asset_ctb);
    UserInstance* user_instance {mpEvent->getUserInstance()};
    System* system {user_instance->getUser()->getSystem()};
    AssetExecutor* child_executor {system->allocAssetExecutor(event)};

    mpChild = reinterpret_cast<ContainerBase*>(child_executor);
    
    if (child_executor == nullptr) {
        user_instance->printLogEmitFailed(*mpEvent, "alloc AssetExecutor[%s] failed", 
                                          solveOffset<const char>(asset_ctb.keyNamePos));
        return false;
    }

    auto& accessor {user_instance->getUserResource()->getAccessor()};
    f32 duration {accessor.getDuration(asset_ctb, user_instance)};
    if (duration > 0.0f) {
        f32 delay {accessor.getDelayWithOverwrite(asset_ctb, 
                                                  reinterpret_cast<u64>(event->getOverwriteParam()), 
                                                  user_instance)};
        duration += delay;
    }
    else {
        duration = -1.0f;
    }

    mOverwriteDuration = duration;
    mDelay = duration;
    return true;
}

bool MonoContainer::start()
{
    if (mpChild != nullptr) {
        auto* child_executor {reinterpret_cast<AssetExecutor*>(mpChild)};
        auto* asset_ctb {mpAssetCallTable};
        auto* child_event {child_executor->getEvent()};
        child_executor->setUserInstance(mpEvent->getUserInstance());
        child_executor->setAssetCallTable(asset_ctb);

        child_executor->setOverwriteParam(child_event->getOverwriteParam(), child_event->getBoneMtx());

        if (!child_event->getAliveAssetExecutors().isNodeLinked(child_executor))
            child_event->getAliveAssetExecutors().pushBack(child_executor);
    
        return child_executor->activateImpl_();
    }

    return false;
    
}
} // namespace xlink2