#include <cstring>

#include "xlink2/xlink2UserResource.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
UserResource::UserResource(User* user) 
{
    mUser = user;
    mResMode = ResMode::Rom;
    mParams[0] = nullptr;
    mParams[1] = nullptr;
}

UserResource::~UserResource() = default;

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
        return param->userBinParam.pResUserHeader;
    return nullptr;
}

bool UserResource::searchAssetCallTableByName(Locator* locator, const char* name) const
{
    ResAssetCallTable* asset_ctb {doBinarySearchAsset_(name, TriggerType::Action)};

    locator->setAssetCallTable(asset_ctb);
    return asset_ctb != nullptr;
}

ResAssetCallTable* UserResource::searchAssetCallTableByName(const char* name) const
{
    return doBinarySearchAsset_(name, TriggerType::Action);
}

ResAssetCallTable* UserResource::doBinarySearchAsset_(const char* name, TriggerType type) const 
{
    UserResourceParam* param {getParam()};
    if (param != nullptr && param->isSetup) {
        if (param->userBinParam.pResUserHeader->numCallTable == 0)
            return nullptr;

        s32 a {0};
        s32 b = static_cast<s32>(param->userBinParam.pResUserHeader->numCallTable) - 1;
#ifdef MATCHING_HACK_NX_CLANG
        asm("");
#endif

        while (a <= b) {
            const s32 m = (a + b) / 2;
            auto* asset_param {&param->userBinParam.pResAssetCallTable[param->userBinParam.pSortedAssetIdTable[m]]};
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

bool UserResource::searchAssetCallTableByHash(Locator* locator, u32 name_hash) const
{
    UserResourceParam* param {getParam()};
    if (param != nullptr && param->isSetup && param->userBinParam.pResUserHeader->numCallTable != 0) {
        for (u32 i {0}; i < param->userBinParam.pResUserHeader->numCallTable; ++i) {
            if (param->userBinParam.pResAssetCallTable[i].keyNameHash == name_hash) {
                locator->setAssetCallTable(&param->userBinParam.pResAssetCallTable[i]);
                return true;
            }
        }
    }

    return false;
}

ResAssetCallTable* UserResource::getAssetCallTableItem(s32 idx) const 
{
    UserResourceParam* param = getParamWithSetupCheck();
    
    if (param && param->isSetup) {
        if (idx >= 0 && static_cast<s32>(param->userBinParam.pResUserHeader->numCallTable) > idx)
            return &param->userBinParam.pResAssetCallTable[idx];
    }
    return nullptr;
}

ResActionTrigger* UserResource::getActionTriggerTableItem(s32 idx) const 
{
    UserResourceParam* param = getParamWithSetupCheck();
    
    if (param != nullptr && param->isSetup) {
        if (idx >= 0 && static_cast<s32>(param->userBinParam.pResUserHeader->numResActionTrigger) > idx)
            return &param->userBinParam.pResActionTriggerTable[idx];
    }
    return nullptr;
}

ResPropertyTrigger* UserResource::getPropertyTriggerTableItem(s32 idx) const 
{
    UserResourceParam* param = getParamWithSetupCheck();
    
    if (param != nullptr && param->isSetup) {
        if (idx >= 0 && static_cast<s32>(param->userBinParam.pResUserHeader->numResPropertyTrigger) > idx)
            return &param->userBinParam.pResPropertyTriggerTable[idx];
    }
    return nullptr;
}

ResAlwaysTrigger* UserResource::getAlwaysTriggerTableItem(s32 idx) const 
{
    UserResourceParam* param = getParamWithSetupCheck();
    
    if (param != nullptr && param->isSetup) {
        if (idx >= 0 && static_cast<s32>(param->userBinParam.pResUserHeader->numResAlwaysTrigger) > idx)
            return &param->userBinParam.pResAlwaysTriggerTable[idx];
    }
    return nullptr;
}

void UserResource::destroy() 
{
    if (mParams[0] != nullptr)
        this->freeResourceParam_(mParams[0]);

    if (mParams[1] != nullptr)
        this->freeResourceParam_(mParams[1]);
}

void UserResource::freeResourceParam_(UserResourceParam* param) 
{
    param->conditionTableBuffer.freeBuffer();
    param->callTableBuffer.freeBuffer();
    param->actionBuffer.freeBuffer();
}

bool UserResource::doBinarySearchToNameArray_(s32* value_idx, const char* name, u32* name_refs, u32 num_item) 
{
    s32 a {0};
    s32 b = num_item - 1;

    while (a <= b) {
        const s32 m = (a + b) / 2;
        char* key_name {calcOffset<char>(name_refs[m])};

        const s32 c {strcmp(name, key_name)};
        if (c == 0) {
            *value_idx = m;
            return true;
        }

        if (c > 0)
            a = m + 1;
        else
            b = m - 1;
    }

    return false;
}

// WIP
void UserResource::solveNeedObserveFlag_(UserResourceParam* param)
{
    ResUserHeader* user_header {param->userBinParam.pResUserHeader};

    if (user_header->numCallTable != 0) {
        ResAssetCallTable* asset_ctb {param->userBinParam.pResAssetCallTable};

        for (u32 i {0}; i < user_header->numCallTable; ++i) {
            s32 parent_index {asset_ctb[i].parentIndex};
            if (parent_index < 0 || asset_ctb[parent_index].flag.isOffBit(0))
                solveNeedObserveFlagImpl_(i, &asset_ctb[i], param, user_header);
        }
    }
}

ResAssetCallTable* UserResource::searchAssetAllResource(const char* name) const
{
    UserResourceParam* param {getParam()};
    if (param != nullptr && param->isSetup && param->userBinParam.pResUserHeader->numCallTable != 0) {
        for (u64 i {0}; i < param->userBinParam.pResUserHeader->numCallTable; ++i) {
            char* key_name {calcOffset<char>(param->userBinParam.pResAssetCallTable[i].keyNamePos)};
            if (strcmp(name, key_name) == 0)
                return &param->userBinParam.pResAssetCallTable[i];
        }
    }

    return nullptr;
}

bool UserResource::hasGlobalPropertyTrigger() const 
{
    UserResourceParam* param {getParam()};

    if (param != nullptr && param->isSetup) {
        for (u32 i{0}; i < param->userBinParam.pResUserHeader->numResProperty; ++i) {
            if (param->userBinParam.pResPropertyTable[i].isGlobal)
                return true;
        }
    }

    return false;
}

u64 UserResource::getEditorSetupTime() const {
    return 0;
}

void UserResource::checkAndAddErrorMultipleKeyByTrigger(const ResAssetCallTable& /*unused*/,
                                                        TriggerType /*unused*/) {}

bool UserResource::searchAssetCallTableByGuid(Locator* locator, s32 guid) const
{
    locator->reset();
    UserResourceParam* param {getParam()};
    if (param != nullptr && param->isSetup) {
        for (u32 i{0}; i < param->userBinParam.pResUserHeader->numCallTable; ++i) {
            if (param->userBinParam.pResAssetCallTable[i].guid == guid) {
                locator->setAssetCallTable(&param->userBinParam.pResAssetCallTable[i]);
                return true;
            }
        }
    }
    return false;
}

void UserResource::onSetupResourceParam_(UserResourceParam* /*unused*/,
                                         const ParamDefineTable* /*unused*/,
                                         sead::Heap* /*unused*/) {}
}  // namespace xlink2