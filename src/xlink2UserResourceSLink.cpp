#include <xlink2/xlink2UserResourceSLink.h>

namespace xlink2 {
UserResourceSLink::UserResourceSLink(User* user, sead::Heap* heap)
    : UserResource(user)
{
    mAccessor.setSystem(getSystem());
    mAccessor.setUserResource(this);
}

UserResourceSLink::~UserResourceSLink() = default;

const ResParam* UserResourceSLink::getUserParam() const
{
    auto* param {static_cast<UserResourceParamSLink*>(getParam())};
    if (param != nullptr && param->isSetup)
        return &param->userParam;

    return nullptr;
}

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

ResourceAccessorSLink* UserResourceSLink::getAccessorPtr()
{
    return &mAccessor;
}

SystemSLink* UserResourceSLink::getSystem() const 
{
    return SystemSLink::instance();
}
} // namespace xlink2