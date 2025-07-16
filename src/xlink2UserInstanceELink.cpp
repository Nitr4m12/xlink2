#include <xlink2/xlink2UserInstanceELink.h>

#include <xlink2/xlink2UserResourceELink.h>
#include <xlink2/xlink2UserInstanceParam.h>

namespace xlink2 {
void UserInstanceELink::freeInstanceParam_(UserInstanceParam* param, ResMode mode) {
    if (param != nullptr) {
        UserInstance::freeInstanceParam_(param, mode);
        delete param;
    }
}

ResourceAccessorELink* UserInstanceELink::getResourceAccessor() const {
    return static_cast<ResourceAccessorELink*>(mUser->getUserResource()->getResourceAccessor());
}

UserResourceELink* UserInstanceELink::getResourceELink() const {
    return static_cast<UserResourceELink*>(mUser->getUserResource());
}

void UserInstanceELink::onDestroy_() {}
}  // namespace xlink2