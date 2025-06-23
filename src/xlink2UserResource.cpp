#include <cstring>

#include "xlink2/xlink2UserResource.h"

#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResUserHeader.h"
#include "xlink2/xlink2UserResourceParam.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
UserResource::UserResource(User* user) 
{
    mUser = user;
    mResMode = ResMode::Rom;
    mParams[0] = nullptr;
    mParams[1] = nullptr;
}

void UserResource::setup(sead::Heap* heap) 
{
    sead::Heap* user_heap;
    System* sys;

    if (mParams[0] == nullptr || !mParams[0]->isSetup) {
        sys = mUser->getSystem();
        user_heap = sys->getUserHeap();
        if (!user_heap || user_heap->getFreeSize() / 1024 < 5) {
            user_heap = heap;
        }
        setupRomResourceParam_(user_heap);
    }

    sys = getSystem();

    if (sys->getEditorBuffer() && sys->isServerConnecting()) {
        EditorResourceParam* editor_res_param
                    {sys->getEditorBuffer()->searchEditorResourceParam(mUser->getUserName())};
        if (editor_res_param) {
            sead::Heap* primary_heap {sys->getPrimaryHeap()};
            if (mParams[1])
                freeResourceParam_(mParams[1]);
            
            UserResourceParam* res_param {allocResourceParam_(primary_heap)};
            mParams[1] = res_param;
            ResUserHeader* user_header {editor_res_param->pResUserHeader};

            System* new_res_system {getSystem()};
            setupResourceParam_(res_param, user_header, editor_res_param,
                                new_res_system->getEditorBuffer()->getParamDefineTable(),
                                primary_heap);

            this->mResMode = ResMode::Editor;
        }
    }
}

void UserResource::setupEditorResourceParam(EditorResourceParam* param, sead::Heap* heap)
{
    if (mParams[1] != nullptr)
        freeResourceParam_(mParams[1]);

    mParams[1] = allocResourceParam_(heap);

    setupResourceParam_(mParams[1], param->pResUserHeader, param, getSystem()->getEditorBuffer()->getParamDefineTable(), heap);
}

const ResUserHeader* UserResource::getUserHeader() const 
{
    auto* param = mParams[int(mResMode)];

    if (param != nullptr && param->isSetup)
        return param->resUserHeader;
    return nullptr;
}

bool UserResource::searchAssetCallTableByName(Locator* locator, const char* name) const
{
    UserResourceParam* param {getParam()};
    s32 num_call_table {(s32)param->resUserHeader->numCallTable};
    ResAssetCallTable* asset_ctb {param->resAssetCallTable};
    if (param != nullptr && param->isSetup) {
        s32 a {0};
        s32 b {(s32)param->resUserHeader->numCallTable - 1};

        while (a < b) {
            s32 m = a + b;
            if (m < 0)
                ++m;
            
            m /= 2;
            auto* asset_param {asset_ctb + param->sortedAssetIdTable[m]};
            if (asset_param == nullptr)
                asset_ctb = nullptr;

            char* key_name {calcOffset<char>(asset_param->keyNamePos)};

            s32 result {strcmp(name, key_name)};
            if (result == 0)
                asset_ctb = asset_param;

            if (0 < result) {
                ++a;
            }
            
            b = result < 0 ? m - 1 : m;
        }

    }

    locator->setAssetCallTable(asset_ctb);
    return asset_ctb != nullptr;
}

ResAssetCallTable* UserResource::doBinarySearchAsset_(const char* name, TriggerType type) const 
{
    UserResourceParam* param {getParam()};
    if (param != nullptr && param->isSetup) {
        if (param->resUserHeader->numCallTable == 0)
            return nullptr;

        s32 a {0};
        s32 b {(s32)param->resUserHeader->numCallTable - 1};
#ifdef MATCHING_HACK_NX_CLANG
        asm("");
#endif

        while (a <= b) {
            const s32 m = (a + b) / 2;
            auto* asset_param {&param->resAssetCallTable[param->sortedAssetIdTable[m]]};
            if (asset_param == nullptr)
                return nullptr;

            char* key_name {calcOffset<char>(asset_param->keyNamePos)};

            const s32 c {strcmp(name, key_name)};
            if (c == 0)
                return asset_param;

            if (c > 0)
                a = m + 1;
            else
                b = m - 1;
        }

    }

    return nullptr;
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
ResActionTrigger* UserResource::getActionTriggerTableItem(s32 index) const {
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