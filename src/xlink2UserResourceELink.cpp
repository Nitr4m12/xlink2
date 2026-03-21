#include <xlink2/xlink2UserResourceELink.h>

#include <xlink2/xlink2SystemELink.h>

namespace xlink2 {
UserResourceELink::UserResourceELink(User* user, sead::Heap* heap)
    : UserResource(user)
{
    mAccessor.setSystem(SystemELink::instance());
    mAccessor.setUserResource(this);
    _0x28 = false;
}

SolvedAssetParamELink* UserResourceELink::getSolvedAssetParameterELink(const ResAssetCallTable& asset_ctb) const
{
    auto* param {getParamWithSetupCheck()};
    if (param != nullptr && asset_ctb.assetId > -1) {
        auto& ptrs = static_cast<UserResourceParamELink*>(param)->solvedAssetParamPtrs;
        return ptrs.unsafeAt(asset_ctb.assetId);
    }
    return nullptr;
}

// SystemELink* UserResourceELink::getSystem() const {
//     return SystemELink::sInstance;
// }
const ResourceAccessorELink& UserResourceELink::getAccessor() const
{
    return mAccessor;
}
}