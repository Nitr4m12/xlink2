#include <xlink2/xlink2UserResourceSLink.h>

namespace xlink2 {
UserResourceSLink::UserResourceSLink(User* user, sead::Heap* heap)
    : UserResource(user)
{
    mAccessor.setSystem(SystemSLink::instance());
    mAccessor.setUserResource(this);
}

UserResourceSLink::~UserResourceSLink() = default;

UserResourceParamSLink* UserResourceSLink::allocResourceParam_(sead::Heap* heap)
{
    auto* param {new(heap) UserResourceParamSLink};
    param->accessor = &mAccessor;
    return param;
}

void UserResourceSLink::freeResourceParam_(UserResourceParam* param)
{
    auto* slink_param {static_cast<UserResourceParamSLink*>(param)};
    if (slink_param != nullptr) {
        UserResource::freeResourceParam_(slink_param);
        delete param;
    }
}

const ResourceAccessorSLink& UserResourceSLink::getAccessor() const
{
    return mAccessor;
}
} // namespace xlink2