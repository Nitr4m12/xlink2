#include <xlink2/xlink2UserInstanceSLink.h>

#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2HoldMgr.h>
#include <xlink2/xlink2ILockProxy.h>
#include <xlink2/xlink2SystemSLink.h>
#include <xlink2/xlink2UserResourceSLink.h>

namespace xlink2 {
UserInstanceSLink::~UserInstanceSLink() = default;

void UserInstanceSLink::searchAndEmit(const char* asset_key_name, HandleSLink* handle)
{
    searchAndEmitImpl(asset_key_name, handle);
}

void UserInstanceSLink::emit(const ResAssetCallTable& asset_ctb, HandleSLink* handle)
{
    Locator locator {asset_ctb};
    emitImpl(locator, handle);
}

void UserInstanceSLink::emit(const Locator& locator, HandleSLink* handle)
{
    emitImpl(locator, handle);
}

void UserInstanceSLink::searchAndHold(const char* name, HandleSLink* handle)
{
    auto* system {mUser->getSystem()};
    system->getHoldMgr()->searchAndHold(name, handle, this);
}

void UserInstanceSLink::fadeIfLoopSound()
{
    {
        auto lock {sead::makeScopedLock(*SystemSLink::sLockProxy)};
        for (auto& event : mEventList)
            event.fadeBySystem();
    }

    mTriggerCtrlMgr.reset();
}

const ResourceAccessorSLink& UserInstanceSLink::getResourceAccessor() const 
{
    return getResourceSLink()->getResourceAccessor();
}

UserResourceSLink* UserInstanceSLink::getResourceSLink() const 
{
    return static_cast<UserResourceSLink*>(mUser->getUserResource());
}

UserInstanceParamSLink* UserInstanceSLink::allocInstanceParam_(sead::Heap* heap)
{
    return new(heap) UserInstanceParamSLink;
}

void UserInstanceSLink::doEventActivatedCallback_(const Locator& locator, Event* event)
{
    auto* system {SystemSLink::instance()};
    auto* event_callback {system->getEventCallback()};
    if (event_callback != nullptr) {
        IEventCallbackSLink::EventArg event_arg;
        event_arg.pUserInstance = this;
        event_arg.pAssetCallTable = locator.getAssetCallTable();
        event_arg.pEvent = static_cast<EventSLink*>(event);
        event_callback->eventActivated(event_arg);
    }

    event_callback = mpEventCallback;
    if (event_callback != nullptr) {
        IEventCallbackSLink::EventArg event_arg;
        event_arg.pUserInstance = this;
        event_arg.pAssetCallTable = locator.getAssetCallTable();
        event_arg.pEvent = static_cast<EventSLink*>(event);
        event_callback->eventActivated(event_arg);
    }
}

}  // namespace xlink2