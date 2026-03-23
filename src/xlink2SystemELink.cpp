#include "xlink2/xlink2SystemELink.h"
#include "xlink2/xlink2AssetExecutorELink.h"
#include "xlink2/xlink2UserResourceELink.h"

namespace xlink2 {
UserInstanceELink* SystemELink::createUserInstance(const UserInstance::CreateArg& arg, sead::Heap* heap, u32 i1)
{
    {
        auto lock {sead::makeScopedLock(*sLockProxy)};
        User* user {searchUserOrCreate_(arg, heap, i1)};
        if (user != nullptr) {
            auto* user_instance = new(heap) UserInstanceELink(arg, this, user, heap);
            user->addInstance(user_instance);
            return user_instance;
        }
    }
    return nullptr;
}

UserResource* SystemELink::createUserResource(User* user, sead::Heap* heap)
{
    return new(heap) UserResourceELink(user, heap);
}

// NON-MATCHING
AssetExecutor* SystemELink::allocAssetExecutor(Event* event)
{
    auto* executor {static_cast<AssetExecutorELink*>(mAssetExecutorHeap->alloc(sizeof(AssetExecutorELink)))};
    if (executor != nullptr) {
        return executor;
    }
    addError(Error::Type::OutOfMemory, event->getUserInstance()->getUser(), "SystemELink::allocAssetExecutor failed.");
    return nullptr;
}

u32 SystemELink::getResourceVersion() const 
{
    return 30;
}

sead::SafeString* SystemELink::getModuleName() const
{
    return &sModuleNameELink;
}

void SystemELink::genMessage(sead::hostio::Context* ctx)
{
#ifdef SEAD_DEBUG
#endif
}

void SystemELink::listenPropertyEvent(const sead::hostio::PropertyEvent* property_event)
{
#ifdef SEAD_DEBUG
#endif
}

const sead::SafeString* SystemELink::getORIconString()
{
    return &sORIconStringELink;
}

Event* SystemELink::getEventFromPool_(u32 idx) const
{
    if (idx < mMaxNumEventPool)
        return &mpEventPool[idx];

    return nullptr;
}

void SystemELink::preDrawInformation_(sead::TextWriter* text_writer) const
{
#ifdef SEAD_DEBUG
#endif
}

void SystemELink::postDrawInformation_(sead::TextWriter* text_writer) const
{
#ifdef SEAD_DEBUG
#endif
}

void SystemELink::drawInformationSystemDetail_(sead::TextWriter* text_writer) const
{
#ifdef SEAD_DEBUG
#endif
}

void SystemELink::drawInformationEvent_(sead::TextWriter* text_writer) const
{
#ifdef SEAD_DEBUG
#endif
}

u32 SystemELink::getUserParamNum() const {
    return 0;
}

ILockProxy* SystemELink::getModuleLockObj() const {
    return sLockProxy;
}

}  // namespace xlink2