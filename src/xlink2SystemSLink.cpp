#include "xlink2/xlink2SystemSLink.h"
#include "xlink2/xlink2ILockProxy.h"
#include "xlink2/xlink2UserResourceSLink.h"

namespace xlink2 {
SystemSLink::SystemSLink() = default;

SystemSLink::~SystemSLink()
{
    if (mpEventPool != nullptr) {
        delete[] (mpEventPool);
        mpEventPool = nullptr;
    }
    if (mIsAllocatedLock) {
        delete sLockProxy;
        sLockProxy = nullptr;
    }
}

UserInstanceSLink* SystemSLink::createUserInstance(const UserInstanceSLink::CreateArgSLink& arg, 
                                                   sead::Heap* heap, u32 i1)
{
    {
        auto lock {sead::makeScopedLock(*sLockProxy)};
        User* user {searchUserOrCreate_(arg, heap, i1)};
        if (user != nullptr) {
            auto* user_instance = new(heap) UserInstanceSLink(arg, this, user, heap);
            user->addInstance(user_instance);
            return user_instance;
        }
    }
    return nullptr;
}

UserResource* SystemSLink::createUserResource(User* user, sead::Heap* heap)
{
    return new(heap) UserResourceSLink(user, heap);
}

u32 SystemSLink::getResourceVersion() const 
{
    return 28;
}

sead::SafeString* SystemSLink::getModuleName() const
{
    return &sModuleNameSLink;
}

u32 SystemSLink::getUserParamNum() const 
{
    return 8;
}

bool SystemSLink::isEnableUserAssetInfoReadable() 
{
    return false;
}

void SystemSLink::stopAllEvent(s32 i1)
{
    {
        auto lock {sead::makeScopedLock(*sLockProxy)};

        for (auto& user : mUserList) {
            for (auto& instance : user.getUserInstanceList())
                static_cast<UserInstanceSLink*>(&instance)->stopAllEvent(i1);
        }
    }
}

void SystemSLink::genMessage(sead::hostio::Context* ctx)
{
#ifdef SEAD_DEBUG
#endif
}

void SystemSLink::listenPropertyEvent(const sead::hostio::PropertyEvent* property_event)
{
#ifdef SEAD_DEBUG
#endif
}

sead::SafeString* SystemSLink::getORIconString()
{
    return &sORIconStringSLink;
}

Event* SystemSLink::getEventFromPool_(u32 idx) const
{
    if (idx < mMaxNumEventPool)
        return &mpEventPool[idx];

    return nullptr;
}

void SystemSLink::drawInformationSystemDetail_(sead::TextWriter* text_writer) const
{
#ifdef SEAD_DEBUG
#endif
}

void SystemSLink::drawInformationEvent_(sead::TextWriter* text_writer) const
{
#ifdef SEAD_DEBUG
#endif
}

void SystemSLink::drawInformationEmitter_(UserInstance* user_instance, 
                                          sead::DrawContext* draw_context, 
                                          sead::TextWriter* text_writer, 
                                          const sead::Camera& camera, 
                                          const sead::Projection& projection, 
                                          const sead::Viewport& viewport) const
{
#ifdef SEAD_DEBUG
#endif
}

ILockProxy* SystemSLink::getModuleLockObj() const 
{
    return sLockProxy;
}
}  // namespace xlink2