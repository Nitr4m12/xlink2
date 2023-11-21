#include "xlink2/xlink2ContainerBase.h"
#include "xlink2/xlink2ContainerCreator.h"

namespace xlink2 {
ContainerBase::ContainerBase() {
    mAssetDuration = 0;
    mChildContainers[0] = nullptr;
    mChildContainers[1] = nullptr;
    mResAssetCallTable = nullptr;
    mEvent = nullptr;
}
ContainerBase::~ContainerBase() = default;

void* ContainerBase::createChildContainer_(ResAssetCallTable const& asset_call_table,
                                           ContainerBase* container) {
    auto* child_container{ContainerCreator::CreateContainer(mEvent, asset_call_table)};

    if (!child_container)
        return nullptr;

    bool started{/*child_container->start()*/};
    if (!(started & 1)) {
        child_container->destroy();
        child_container = nullptr;
    } else if (container)
        mChildContainers[0] = child_container;
    else
        container->mChildContainers[1] = child_container;

    return child_container;
}

void ContainerBase::fade(int p1) {
    for (auto* child_container : mChildContainers) {
        child_container->fade(p1);
    }

    mAssetDuration = 0;
}

void ContainerBase::fadeBySystem() {
    for (auto* child_container : mChildContainers) {
        child_container->fadeBySystem();
    }

    mAssetDuration = 0;
}

bool ContainerBase::initialize(Event* event, const ResAssetCallTable& asset_call_table) {
    mResAssetCallTable = &(ResAssetCallTable&)asset_call_table;
    mEvent = event;
    event->getUserInstance()->getUser()->getUserResource()->getAccessor();
    mAssetDuration = asset_call_table.duration;
    return true;
}

void ContainerBase::kill() {
    for (auto* child_container : mChildContainers) {
        child_container->kill();
    }

    mAssetDuration = 0;
}
}  // namespace xlink2