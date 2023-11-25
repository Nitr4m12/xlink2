#include "xlink2/xlink2ContainerBase.h"
#include "xlink2/xlink2ContainerCreator.h"

namespace xlink2 {
ContainerBase::ContainerBase() {
    mAssetDuration = 0;
    mUnknownContainer = nullptr;
    mChild = nullptr;
    mResAssetCallTable = nullptr;
    mEvent = nullptr;
}
ContainerBase::~ContainerBase() = default;

bool ContainerBase::initialize(Event* event, const ResAssetCallTable& asset_call_table) {
    mResAssetCallTable = &(ResAssetCallTable&)asset_call_table;
    mEvent = event;
    event->getUserInstance()->getUser()->getUserResource()->getAccessor();
    mAssetDuration = asset_call_table.duration;
    return true;
}

// NON-MATCHING: wrong register
void ContainerBase::destroy() {
    auto* child = mChild;
    while (child != nullptr) {
        auto* unk = child;
        child = mUnknownContainer;
        unk->destroy();
    }

    mAssetDuration = 0;
    mChild = nullptr;

    auto* system = mEvent->getUserInstance()->getUser()->getSystem();
    auto* heap = system->getContainerHeap();
    this->~ContainerBase();
    heap->free(this);
}
void ContainerBase::fadeBySystem() {
    for (auto* child = mChild; child != nullptr; child = child->mParent)
        child->fadeBySystem();

    mAssetDuration = 0;
}

void ContainerBase::fade(s32 p1) {
    for (auto* child = mChild; child != nullptr; child = child->mParent)
        child->fade(p1);

    mAssetDuration = 0;
}

void ContainerBase::kill() {
    for (auto* child = mChild; child != nullptr; child = child->mParent)
        child->kill();

    mAssetDuration = 0;
}


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
        mChild = child_container;
    else
        container->mUnknownContainer = child_container;

    return child_container;
}

void ContainerBase::fade(int p1) {
    mUnknownContainer->fade(p1);
    mChild->fade(p1);
    mAssetDuration = 0;
}

void ContainerBase::fadeBySystem() {
    mUnknownContainer->fadeBySystem();
    mChild->fadeBySystem();

    mAssetDuration = 0;
}

void ContainerBase::kill() {
    mUnknownContainer->kill();
    mChild->kill();

    mAssetDuration = 0;
}
}  // namespace xlink2