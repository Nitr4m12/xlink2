#include <xlink2/xlink2UserInstanceELink.h>
#include <xlink2/xlink2UserInstanceParam.h>

namespace xlink2 {
void UserInstanceELink::freeInstanceParam_(UserInstanceParam* param, ResMode mode) {
    if (param != nullptr) {
        UserInstance::freeInstanceParam_(param, mode);
        delete param;
    }
}

ResourceAccessor* UserInstanceELink::getResourceAccessor() const {
    return mUser->getUserResource()->getResourceAccessor();
}

UserResource* UserInstanceELink::getResourceELink() const {
    return mUser->getUserResource();
}

void UserInstanceELink::onDestroy_() {}
}  // namespace xlink2