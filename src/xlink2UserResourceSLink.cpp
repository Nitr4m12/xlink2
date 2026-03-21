#include <xlink2/xlink2UserResourceSLink.h>

namespace xlink2 {
UserResourceSLink::UserResourceSLink(User* user, sead::Heap* heap)
    : UserResource(user)
{
    mAccessor.setSystem(getSystem());
    mAccessor.setUserResource(this);
}

UserResourceSLink::~UserResourceSLink() = default;
} // namespace xlink2