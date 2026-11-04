#include "xlink2/xlink2SystemELink.h"

#include "xlink2/xlink2AssetExecutorELink.h"
#include "xlink2/xlink2UserResourceELink.h"

namespace xlink2 {
UserInstanceELink* SystemELink::createUserInstance(const UserInstance::CreateArg& arg,
                                                   sead::Heap* heap, u32 _i1)
{
    auto lock {sead::makeScopedLock(*sLockProxy)};
    User* user {searchUserOrCreate_(arg, heap, _i1)};
    if (user == nullptr)
        return nullptr;

    auto* user_instance = new (heap) UserInstanceELink(arg, this, user, heap);
    user->addInstance(user_instance);
    return user_instance;
}

UserResource* SystemELink::createUserResource(User* user, sead::Heap* heap)
{
    return new (heap) UserResourceELink(user, heap);
}

// NON-MATCHING: constructor of AssetExecutorELink seems to not inline properly
AssetExecutorELink* SystemELink::allocAssetExecutor(Event* event)
{

    void* alloc_mem {mAssetExecutorHeap->alloc(sizeof(AssetExecutorELink))};
    if (alloc_mem == nullptr) {
        addError(Error::Type::OutOfMemory, event->getUserInstance()->getUser(),
                "SystemELink::allocAssetExecutor failed.");
        return nullptr;
    }

    return new (alloc_mem) AssetExecutorELink(event);
}

u32 SystemELink::getResourceVersion() const
{
    return 30;
}

sead::SafeString* SystemELink::getModuleName() const
{
    return &sModuleNameELink;
}

void SystemELink::genMessage([[maybe_unused]] sead::hostio::Context* ctx)
{
#ifdef SEAD_DEBUG
#endif
}

void SystemELink::listenPropertyEvent(
    [[maybe_unused]] const sead::hostio::PropertyEvent* property_event)
{
#ifdef SEAD_DEBUG
#endif
}

const sead::SafeString* SystemELink::getORIconString()
{
    return &sORIconStringELink;
}

EventELink* SystemELink::getEventFromPool_(u32 idx) const
{
    if (idx >= mMaxNumEventPool)
        return nullptr;

    return &mpEventPool[idx];
}

void SystemELink::preDrawInformation_([[maybe_unused]] sead::TextWriter* text_writer) const
{
#ifdef SEAD_DEBUG
#endif
}

void SystemELink::postDrawInformation_([[maybe_unused]] sead::TextWriter* text_writer) const
{
#ifdef SEAD_DEBUG
#endif
}

void SystemELink::drawInformationSystemDetail_([[maybe_unused]] sead::TextWriter* text_writer) const
{
#ifdef SEAD_DEBUG
#endif
}

void SystemELink::drawInformationEvent_([[maybe_unused]] sead::TextWriter* text_writer) const
{
#ifdef SEAD_DEBUG
#endif
}

u32 SystemELink::getUserParamNum() const
{
    return 0;
}

ILockProxy* SystemELink::getModuleLockObj() const
{
    return sLockProxy;
}

}  // namespace xlink2