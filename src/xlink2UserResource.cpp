#include <xlink2/xlink2UserResource.h>

namespace xlink2 {
UserResource::~UserResource() = default;
UserResource::UserResource(User* user) {
    mUser = user;
    mResMode = (ResMode)0;
    mUserResourceParam = nullptr;
    _1 = nullptr;
}

void UserResource::onSetupResourceParam_(UserResourceParam*, const ParamDefineTable*, sead::Heap*) {}
}  // namespace xlink2