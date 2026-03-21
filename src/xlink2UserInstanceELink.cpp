#include <xlink2/xlink2UserInstanceELink.h>

#include <prim/seadScopedLock.h>

#include <xlink2/xlink2UserResourceELink.h>
#include <xlink2/xlink2UserInstanceParam.h>
#include <xlink2/xlink2ILockProxy.h>
#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HoldMgr.h>
#include <xlink2/xlink2SystemELink.h>
#include <xlink2/xlink2UserInstance.h>

namespace xlink2 {
UserInstanceELink::UserInstanceELink(const UserInstance::CreateArg& arg, System* system, 
                                     User* user, sead::Heap* heap)
    : UserInstance(arg, system, user, heap) {}

UserInstanceELink::~UserInstanceELink() = default;

void UserInstanceELink::searchAndEmit(const char* asset_key_name, HandleELink* handle)
{
    searchAndEmitImpl(asset_key_name, handle);
}

void UserInstanceELink::emit(const Locator& locator, HandleELink* handle)
{
    emitImpl(locator, handle);
}

void UserInstanceELink::searchAndHold(const char* name, HandleELink* handle)
{
    auto* system {mUser->getSystem()};
    system->getHoldMgr()->searchAndHold(name, handle, this);
}

void UserInstanceELink::fadeIfLoopEffect()
{
    {
        auto lock {sead::makeScopedLock(*SystemELink::sLockProxy)};
        for (auto& event : mEventList)
            event.fadeBySystem();
    }

    mTriggerCtrlMgr.reset();
}

const ResourceAccessorELink& UserInstanceELink::getResourceAccessor() const 
{
    return getResourceELink()->getResourceAccessor();
}

UserResourceELink* UserInstanceELink::getResourceELink() const 
{
    return static_cast<UserResourceELink*>(mUser->getUserResource());
}

void UserInstanceELink::onReset_()
{
    mBitFlag.resetBit(6);
    _0xf8 = -1;
}

void UserInstanceELink::onDestroy_() {}

UserInstanceParam* UserInstanceELink::allocInstanceParam_(sead::Heap* heap)
{
    return new(heap) UserInstanceParam;
}

void UserInstanceELink::freeInstanceParam_(UserInstanceParam* param, ResMode mode) 
{
    if (param != nullptr) {
        UserInstance::freeInstanceParam_(param, mode);
        delete param;
    }
}

void UserInstanceELink::onSetupInstanceParam_(ResMode res_mode, sead::Heap* heap)
{
    initModelAssetConnection_(res_mode, mUser->getSystem()->getParamDefineTable(res_mode), heap);
}

u32 UserInstanceELink::getDefaultGroup() const
{
    return mDefaultGroup;
}
}  // namespace xlink2