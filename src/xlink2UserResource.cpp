#include <xlink2/xlink2UserResource.h>

namespace xlink2 {
UserResource::~UserResource() = default;

void UserResource::onSetupResourceParam_(UserResourceParam*, const ParamDefineTable*, sead::Heap*) {}
}  // namespace xlink2