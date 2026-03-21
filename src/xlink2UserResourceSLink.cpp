#include <xlink2/xlink2UserResourceSLink.h>

namespace xlink2 {
UserResourceSLink::UserResourceSLink(User* user, sead::Heap* heap)
    : UserResource(user)
{
    mAccessor.setSystem(getSystem());
    mAccessor.setUserResource(this);
}

UserResourceSLink::~UserResourceSLink() = default;

UserResourceParamSLink* UserResourceSLink::allocResourceParam_(sead::Heap* heap)
{
    auto* param {new(heap) UserResourceParamSLink};
    param->accessor = &mAccessor;
    return param;
}
} // namespace xlink2