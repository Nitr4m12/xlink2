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

u32 SystemSLink::getResourceVersion() const {
    return 0x1c;
}

u32 SystemSLink::getUserParamNum() const {
    return 8;
}

bool SystemSLink::isEnableUserAssetInfoReadable() const {
    return false;
}

ILockProxy* SystemSLink::getModuleLockObj() const {
    return sLockProxy;
}
}  // namespace xlink2