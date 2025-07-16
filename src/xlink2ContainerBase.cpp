#include "xlink2/xlink2ContainerBase.h"

#include "xlink2/xlink2ContainerCreator.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2UserResource.h"

namespace xlink2 {
ContainerBase::ContainerBase()
{
    mAssetDuration = 0;
    mpParent = nullptr;
    mpChild = nullptr;
    mpAssetCallTable = nullptr;
    mpEvent = nullptr;
}
ContainerBase::~ContainerBase() = default;

bool ContainerBase::initialize(Event* event, const ResAssetCallTable& asset_call_table)
{
    mpAssetCallTable = &(ResAssetCallTable&)asset_call_table;
    mpEvent = event;
    event->getUserInstance()->getUser()->getUserResource()->getAccessor();
    mAssetDuration = asset_call_table.duration;
    return true;
}

void ContainerBase::destroy()
{
    auto* child = mpChild;
    while (child != nullptr) {
        auto* unk = child;
        child = child->mpParent;
        unk->destroy();
    }

    mAssetDuration = 0;
    mpChild = nullptr;

    auto* system = mpEvent->getUserInstance()->getUser()->getSystem();
    auto* heap = system->getContainerHeap();
    this->~ContainerBase();
    heap->free(this);
}

void ContainerBase::fadeBySystem()
{
    for (auto* child = mpChild; child != nullptr; child = child->mpParent)
        child->fadeBySystem();

    mAssetDuration = 0;
}

void ContainerBase::fade(s32 p1)
{
    for (auto* child = mpChild; child != nullptr; child = child->mpParent)
        child->fade(p1);

    mAssetDuration = 0;
}

void ContainerBase::kill()
{
    for (auto* child = mpChild; child != nullptr; child = child->mpParent)
        child->kill();

    mAssetDuration = 0;
}

bool ContainerBase::killOneTimeEvent()
{
    bool unk = true;
    for (auto* child = mpChild; child != nullptr; child = child->mpParent) {
        bool unk2 = child->killOneTimeEvent();
        unk = unk2 & unk;
    }
    if (!unk)
        return false;

    mAssetDuration = 0;
    return true;
}

ContainerBase* ContainerBase::createChildContainer_(const ResAssetCallTable& asset_call_table,
                                           ContainerBase* container)
{
    auto* child_container{ContainerCreator::CreateContainer(mpEvent, asset_call_table)};

    if (!child_container)
        return nullptr;

    bool started{child_container->start()};
    if (!started) {
        child_container->destroy();
        child_container = nullptr;
    }
    else if (!container) {
        mpChild = child_container;
    }
    else {
        container->mpParent = child_container;
    }

    return child_container;
}
}  // namespace xlink2
