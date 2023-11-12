#include <xlink2/xlink2UserResource.h>
#include "xlink2/xlink2Util.h"

namespace xlink2 {
UserResource::UserResource(User* user) {
    mUser = user;
    mResMode = ResMode::Rom;
    mParams[0] = nullptr;
    mParams[1] = nullptr;
}

void UserResource::setup(sead::Heap* heap) {
    sead::Heap* user_heap;
    System* sys;

    if (!mParams[0] || !mParams[0]->isSetup) {
        sys = mUser->getSystem();
        user_heap = sys->getUserHeap();
        if (!user_heap || user_heap->getFreeSize() >> 10 < 5) {
            user_heap = heap;
        }
        setupRomResourceParam_(user_heap);
    }

    sys = getSystem();

    if (sys->getEditorBuffer() && sys->isServerConnecting()) {
        EditorResourceParam* editor_res_param{
            sys->getEditorBuffer()->searchEditorResourceParam(mUser->getUserName())};
        if (editor_res_param) {
            sead::Heap* primary_heap{sys->getPrimaryHeap()};
            if (mParams[1])
                freeResourceParam_(mParams[1]);
            UserResourceParam* res_param{allocResourceParam_(primary_heap)};
            mParams[1] = res_param;
            ResUserHeader* user_header{editor_res_param->pResUserHeader};

            System* new_res_system{getSystem()};
            setupResourceParam_(res_param, user_header, editor_res_param,
                                new_res_system->getEditorBuffer()->getParamDefineTable(),
                                primary_heap);

            this->mResMode = ResMode::Editor;
        }
    }
}

const ResUserHeader* UserResource::getUserHeader() const {
    auto* param = mParams[int(mResMode)];

    if (!param || !param->isSetup)
        return 0;
    // return param;
}

// NON-MATCHING
u32* UserResource::doBinarySearchAsset_(const char* name, TriggerType type) const {
    // auto* param{mParams[int(mResMode)]};
    // ResUserHeader* usr_head{};
    // u32 num_asset{usr_head->numCallTable};

    // if (!param || !param->isSetup)
    //     return nullptr;

    // s32 v1 = 0;
    // s64 v2 = param->numCurvePointTable;
    // // ResAssetParam* res_param_table = param->assetParamTable;

    // while (v1 <= num_asset - 1) {
    //     s32 v3 = v1 + (num_asset - 1);
    //     if (v3 < 0)
    //         ++v3;
    //     v3 >>= 1;
    //     u32* asset = &num_asset + (v2 + v3 * 2) * sizeof(Dummy3);
    //     if (asset == nullptr)
    //         return nullptr;

    //     char* asset_name = (char*)(sMinAddressHigh | *asset);
    //     if (*asset < sMinAddressLow)
    //         asset_name += 0x100000000;

    //     if (strcmp(name, asset_name) == 0)
    //         return asset;

    //     s32 v4 = v3 - 1;
    //     if (strcmp(name, asset_name) > 0) {
    //         v1 = v3 + 1;
    //         v4 = num_asset - 1;
    //     }
    // }
}

// // NON_MATCHING: one sub instruction reordered
ResAssetCallTable* UserResource::getAssetCallTableItem(s32 index) const {
    auto* param = mParams[int(mResMode)];
    ResUserHeader* usr_head {nullptr};
    if (!param || !param->isSetup || index >= usr_head->numCallTable || index < 0)
        return nullptr;
    //return &param->assetParamTable[index * sizeof(Dummy3)];
}

// NON_MATCHING: one sub instruction reordered
void* UserResource::getActionTriggerTableItem(s32 index) const {
    // auto* param = mParams[int(mResMode)];
    // ResUserHeader* usr_head {nullptr};

    // if (!param || !param->isSetup || index >= usr_head->numResActionTrigger || index < 0)
    //     return nullptr;
    // return &param->directValueTable[index * sizeof(Dummy)];
}

// NON_MATCHING: one sub instruction reordered
ResAlwaysTrigger* UserResource::getAlwaysTriggerTableItem(s32 index) const {
    // auto* param = mParams[int(mResMode)];
    // ResUserHeader* usr_head{nullptr};

    // if (!param || !param->isSetup || index >= usr_head->numResAlwaysTrigger || index < 0)
    //     return nullptr;
    // return &param->curvePointTable[index * sizeof(Dummy2)];
}

void UserResource::destroy() {
    if (mParams[0] != nullptr)
        this->freeResourceParam_(mParams[0]);

    if (mParams[1] != nullptr)
        this->freeResourceParam_(mParams[1]);
}

// NON-MATCHING
void UserResource::freeResourceParam_(UserResourceParam* param) {
    // if (param->nameTablePos != 0) {
    //     delete[] param->resourceAccessor;
    //     param->resourceAccessor = nullptr;
    //     param->conditionTablePos = 0;
    // }

    // param->resCallTableBuffer.freeBuffer();
    // param->actionTriggerBoolBuffer.freeBuffer();
}

void UserResource::checkAndAddErrorMultipleKeyByTrigger(const ResAssetCallTable& /*unused*/,
                                                        TriggerType /*unused*/) {}

u64 UserResource::getEditorSetupTime() const {
    return 0;
}

bool UserResource::hasGlobalPropertyTrigger() const {
    // auto* param{mParams[int(mResMode)]};
    // ResUserHeader* usr_head {nullptr};

    // if (!param || !param->isSetup || usr_head->numResProperty == 0)
    //     return false;

    // ResRandomCallTable* random_table{param->randomCallTable};
    // f32 max_val{random_table->maxValue};
    // for (int i{0}; i < usr_head->numResProperty; ++i) {
    //     if (max_val != 0)
    //         return true;

    //     max_val += 16;
    // }
    // return false;
}

UserResource::~UserResource() = default;

void UserResource::onSetupResourceParam_(UserResourceParam* /*unused*/,
                                         const ParamDefineTable* /*unused*/,
                                         sead::Heap* /*unused*/) {}
}  // namespace xlink2