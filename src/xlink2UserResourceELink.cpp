#include <xlink2/xlink2UserResourceELink.h>
#include "xlink2/xlink2Util.h"

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

// WIP: Needs more of SystemELink
void UserResourceELink::releaseOneEmitterInstance_(UserResourceParamELink* param, const ParamDefineTable* pdt)
{
    if (_0x28 && mResMode != ResMode::Editor) {
        _0x28 = false;
        u32 name_table_pos {param->pCommonResourceParam->nameTablePos};
        if (name_table_pos != 0) {
            auto* user_header {param->userBinParam.pResUserHeader};
            for (u32 i {0}; i < user_header->numCallTable; ++i) {
                auto& asset_ctb_item {param->userBinParam.pResAssetCallTable[i]};
                if ((asset_ctb_item.flag & 1) == 0) {
                    auto* res_param {mAccessor.getResParamFromAssetParamPos(asset_ctb_item.paramStartPos, 1)};
                    const char* runtime_asset_name {};
                    if (res_param != nullptr)
                        runtime_asset_name = solveOffset<const char>(res_param->getValue());
                    else
                       runtime_asset_name = pdt->getAssetParamDefaultValueString(1);

                    if (runtime_asset_name != nullptr && getAccessor().isUseOneEmitter(asset_ctb_item)) {
                        // OneEmitterMgr* one_emitter_mgr {getSystem()->getOneEmitterMgr()};
                        // one_emitter_mgr->releaseOneEmitterInstance(runtime_asset_name);
                    }
                }
            }
        }
    }
}

void UserResourceELink::onSetupResourceParam_(UserResourceParam* param, const ParamDefineTable* pdt, sead::Heap* heap)
{
    auto* elink_param {static_cast<UserResourceParamELink*>(param)};
    u32 num_asset {elink_param->userBinParam.pResUserHeader->numAsset};
    if (num_asset > 0)
        elink_param->solvedAssetParamBuffer.allocBufferAssert(num_asset, heap);

    auto* leader_instance {static_cast<UserInstanceELink*>(mUser->getLeaderInstance())};
    solveAssetParam_(elink_param, pdt, leader_instance->getPtclResourceAccessor());
    solveNeedObserveFlag_(param);
}

const ResourceAccessorELink& UserResourceELink::getAccessor() const
{
    return mAccessor;
}

ResourceAccessorELink* UserResourceELink::getAccessorPtr()
{
    return &mAccessor;
}

SystemELink* UserResourceELink::getSystem() const 
{
    return SystemELink::instance();
}
} // namespace xlink2