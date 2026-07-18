#include <xlink2/xlink2UserInstanceSLink.h>

#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2HoldMgr.h>
#include <xlink2/xlink2ILockProxy.h>
#include <xlink2/xlink2SystemSLink.h>
#include <xlink2/xlink2UserResourceSLink.h>

namespace xlink2 {
UserInstanceSLink::CreateArgSLink::CreateArgSLink(const char* name, IUser* iuser)
    : UserInstance::CreateArg(name, iuser) {}

UserInstanceSLink::CreateArgSLink::CreateArgSLink(const UserInstance::CreateArg& other)
    : UserInstance::CreateArg(other) {}

UserInstanceSLink::CreateArgSLink::CreateArgSLink(const CreateArgSLink& other)
    : UserInstance::CreateArg(other), _0x40(other._0x40), _0x48(other._0x48) {}

UserInstanceSLink::AssetLimiter::AssetLimiter(s32 num_param, sead::Heap* heap)
{
    mParamBuffer.allocBufferAssert(num_param, heap);
}

UserInstanceSLink::AssetLimiter::~AssetLimiter()
{
    mParamBuffer.freeBuffer();
}

void UserInstanceSLink::AssetLimiter::clear()
{
    for (int i {0}; i < mParamBuffer.size(); ++i)
        mParamBuffer[i].assetExecutorPtrs.clear();
}

void UserInstanceSLink::AssetLimiter::initialize(s32 param_idx, const char* group_name, const ArrangeGroupParam& group_param)
{
    mParamBuffer[param_idx].groupName = group_name;
    mParamBuffer[param_idx].limitType = group_param.limitType;
    mParamBuffer[param_idx].limitThreshold = group_param.limitThreshold;
    mParamBuffer[param_idx]._0xa0 = !group_param._0x6;
}

UserInstanceSLink::~UserInstanceSLink() = default;

HandleSLink UserInstanceSLink::searchAndEmit(const char* asset_key_name)
{
    return {this, asset_key_name};
}

void UserInstanceSLink::searchAndEmit(const char* asset_key_name, HandleSLink* handle)
{
    searchAndEmitImpl(asset_key_name, handle);
}

HandleSLink UserInstanceSLink::emit(const Locator& locator)
{
    return {this, locator};
}

void UserInstanceSLink::emit(const ResAssetCallTable& asset_ctb, HandleSLink* handle)
{
    Locator locator {asset_ctb};
    emitImpl(locator, handle);
}

HandleSLink UserInstanceSLink::emit(const ResAssetCallTable& asset_ctb)
{
    return {this, asset_ctb};
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

void UserInstanceSLink::stopAllEvent(s32 fade_param)
{
    {
        auto lock {sead::makeScopedLock(*SystemSLink::sLockProxy)};
        for (auto& event : mEventList)
            event.fade(fade_param);
    }
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

bool UserInstanceSLink::doEventActivatingCallback_(const Locator& locator)
{
    auto* system {SystemSLink::instance()};
    auto* event_callback {system->getEventCallback()};

    bool is_activating {false};

    if (event_callback != nullptr) {
        IEventCallbackSLink::EventArg event_arg;
        event_arg.pUserInstance = this;
        event_arg.pAssetCallTable = locator.getAssetCallTable();
        is_activating = event_callback->eventActivating(event_arg);
    }

    bool is_event_activating {false};

    event_callback = mpEventCallback;
    if (event_callback != nullptr) {
        IEventCallbackSLink::EventArg event_arg;
        event_arg.pUserInstance = this;
        event_arg.pAssetCallTable = locator.getAssetCallTable();
        is_event_activating = event_callback->eventActivating(event_arg);
        is_activating = is_event_activating || is_activating;
    }

    return is_activating;
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