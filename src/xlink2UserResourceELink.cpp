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

UserResourceELink::~UserResourceELink() = default;

SolvedAssetParamELink* UserResourceELink::getSolvedAssetParameterELink(const ResAssetCallTable& asset_ctb) const
{
    auto* param {getParamWithSetupCheck()};
    if (param != nullptr && asset_ctb.assetId > -1) {
        auto& buffer = static_cast<UserResourceParamELink*>(param)->solvedAssetParamBuffer;
        return &buffer[asset_ctb.assetId];
    }
    return nullptr;
}

void UserResourceELink::solveResourceForChangeEset()
{
    auto* param {static_cast<UserResourceParamELink*>(getParam())};
    if (param != nullptr && param->isSetup) {
        auto* user_instance {static_cast<UserInstanceELink*>(mUser->getLeaderInstance())};
        auto* ptcl_accessor {user_instance->getPtclResourceAccessor()};
        auto* instance_param {static_cast<UserResourceParamELink*>(getParam())};
        auto* pdt {getSystem()->getParamDefineTable(mResMode)};
        solveAssetParam_(instance_param, pdt, ptcl_accessor);
        solveNeedObserveFlag_(getParam());
    }
}

UserResourceParamELink* UserResourceELink::allocResourceParam_(sead::Heap* heap)
{
    auto* param {new(heap) UserResourceParamELink};
    param->accessor = &mAccessor;
    return param;
}

void UserResourceELink::freeResourceParam_(UserResourceParam* param)
{
    auto* elink_param {static_cast<UserResourceParamELink*>(param)};
    if (elink_param != nullptr) {
        auto* local_param {static_cast<UserResourceParamELink*>(getParam())};
        auto* pdt {getSystem()->getParamDefineTable(mResMode)};
        releaseOneEmitterInstance_(local_param, pdt);
        UserResource::freeResourceParam_(elink_param);
        elink_param->solvedAssetParamBuffer.freeBuffer();
        delete param;
    }
}

// SystemELink* UserResourceELink::getSystem() const {
//     return SystemELink::sInstance;
// }
const ResourceAccessorELink& UserResourceELink::getAccessor() const
{
    return mAccessor;
}
}