#include "xlink2/xlink2UserResource.h"

#include <cstring>

#include "xlink2/xlink2EditorBuffer.h"
#include "xlink2/xlink2ResourceBuffer.h"
#include "xlink2/xlink2ResourceParamCreator.h"
#include "xlink2/xlink2ResourceUtil.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
UserResource::UserResource(User* user) : mUser(user) {}

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

    if (sys->getEditorBuffer() == nullptr || !sys->isServerConnecting())
        return;

    EditorBuffer* editor_buffer {sys->getEditorBuffer()};
    const char* user_name {mUser->getUserName()};
    EditorResourceParam* editor_res_param {editor_buffer->searchEditorResourceParam(user_name)};
    if (editor_res_param == nullptr)
        return;

    sead::Heap* primary_heap {sys->getPrimaryHeap()};
    if (mParams[1])
        freeResourceParam_(mParams[1]);

    UserResourceParam* res_param {allocResourceParam_(primary_heap)};
    mParams[1] = res_param;
    ResUserHeader* user_header {editor_res_param->pResUserHeader};

    System* new_res_system {getSystem()};
    setupResourceParam_(res_param, user_header, editor_res_param,
                        new_res_system->getEditorBuffer()->getParamDefineTable(), primary_heap);

    mResMode = ResMode::Editor;
}

void UserResource::setupRomResourceParam_(sead::Heap* heap)
{
    if (mParams[0] != nullptr)
        return;

    UserResourceParam* param {allocResourceParam_(heap)};
    mParams[0] = param;
    System* system {getSystem()};
    ResourceBuffer* resource_buffer {system->getResourceBuffer()};
    ResUserHeader* user_header {resource_buffer->searchResUserHeader(mUser->getUserName())};
    RomResourceParam* rom_resource_param {};
    if (user_header == nullptr) {
        getSystem();

        ResUserHeader* dummy_header {ResourceBuffer::getEmptyUserHeader()};
        dummy_header->isSetup = true;
        user_header = dummy_header;

        RomResourceParam* dummy_param {ResourceBuffer::getEmptyRomResourceParam()};
        dummy_param->isInitialized = true;
        rom_resource_param = dummy_param;
    }
    else {
        rom_resource_param = const_cast<RomResourceParam*>(&resource_buffer->getRomResourceParam());
    }
    setupResourceParam_(mParams[0], user_header, rom_resource_param,
                        resource_buffer->getParamDefineTable(), heap);
}

void UserResource::setupEditorResourceParam(EditorResourceParam* param, sead::Heap* heap)
{
    if (mParams[1] != nullptr)
        freeResourceParam_(mParams[1]);

    mParams[1] = allocResourceParam_(heap);

    setupResourceParam_(mParams[1], param->pResUserHeader, param,
                        getSystem()->getEditorBuffer()->getParamDefineTable(), heap);
}

const ResUserHeader* UserResource::getUserHeader() const
{
    auto* param {mParams[s32(mResMode)]};
    if (param == nullptr || !param->isSetup)
        return nullptr;

    return param->userBinParam.pResUserHeader;
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

ResAssetCallTable* UserResource::doBinarySearchAsset_(const char* name,
                                                      [[maybe_unused]] TriggerType type) const
{
    UserResourceParam* param {getParamWithSetupCheck()};
    if (param == nullptr)
        return nullptr;

    if (param->userBinParam.pResUserHeader->numCallTable == 0)
        return nullptr;

    s32 a {0};
    s32 b = static_cast<s32>(param->userBinParam.pResUserHeader->numCallTable) - 1;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif

    while (a <= b) {
        const s32 m = (a + b) / 2;
        const u16 asset_idx {param->userBinParam.pSortedAssetIdTable[m]};
        auto* asset_ctb {&param->userBinParam.pResAssetCallTable[asset_idx]};
        if (asset_ctb == nullptr)
            return nullptr;

        char* key_name {solveOffset<char>(asset_ctb->keyNamePos)};

        const s32 c {strcmp(name, key_name)};
        if (c == 0)
            return asset_ctb;

        if (c > 0)
            a = m + 1;
        else
            b = m - 1;
    }

    return nullptr;
}

bool UserResource::searchAssetCallTableByHash(Locator* locator, u32 name_hash) const
{
    UserResourceParam* param {getParamWithSetupCheck()};
    if (param == nullptr)
        return false;

    for (u32 i {0}; i < param->userBinParam.pResUserHeader->numCallTable; ++i) {
        if (param->userBinParam.pResAssetCallTable[i].keyNameHash == name_hash) {
            locator->setAssetCallTable(&param->userBinParam.pResAssetCallTable[i]);
            return true;
        }
    }

    return false;
}

ResAssetCallTable* UserResource::getAssetCallTableItem(s32 idx) const
{
    UserResourceParam* param {getParamWithSetupCheck()};

    if (param == nullptr || !param->isSetup)
        return nullptr;

    if (idx < 0)
        return nullptr;

    s32 num_call_table {static_cast<s32>(param->userBinParam.pResUserHeader->numCallTable)};
    if (num_call_table <= idx)
        return nullptr;

    return &param->userBinParam.pResAssetCallTable[idx];
}

ResActionTrigger* UserResource::getActionTriggerTableItem(s32 idx) const
{
    UserResourceParam* param {getParamWithSetupCheck()};

    if (param == nullptr || !param->isSetup)
        return nullptr;

    if (idx < 0)
        return nullptr;

    const ResUserHeader* user_header {param->userBinParam.pResUserHeader};
    s32 num_action_trigger {static_cast<s32>(user_header->numResActionTrigger)};
    if (num_action_trigger <= idx)
        return nullptr;

    return &param->userBinParam.pResActionTriggerTable[idx];
}

ResPropertyTrigger* UserResource::getPropertyTriggerTableItem(s32 idx) const
{
    UserResourceParam* param {getParamWithSetupCheck()};
    if (param == nullptr || !param->isSetup)
        return nullptr;

    if (idx < 0)
        return nullptr;

    const ResUserHeader* user_header {param->userBinParam.pResUserHeader};
    s32 num_property_trigger {static_cast<s32>(user_header->numResPropertyTrigger)};
    if (num_property_trigger <= idx)
        return nullptr;

    return &param->userBinParam.pResPropertyTriggerTable[idx];
}

ResAlwaysTrigger* UserResource::getAlwaysTriggerTableItem(s32 idx) const
{
    UserResourceParam* param {getParamWithSetupCheck()};
    if (param == nullptr || !param->isSetup)
        return nullptr;

    if (idx < 0)
        return nullptr;

    const ResUserHeader* user_header {param->userBinParam.pResUserHeader};
    s32 num_always_trigger {static_cast<s32>(user_header->numResAlwaysTrigger)};
    if (num_always_trigger <= idx)
        return nullptr;

    return &param->userBinParam.pResAlwaysTriggerTable[idx];
}

void UserResource::destroy()
{
    if (mParams[0] != nullptr)
        freeResourceParam_(mParams[0]);

    if (mParams[1] != nullptr)
        freeResourceParam_(mParams[1]);
}

void UserResource::freeResourceParam_(UserResourceParam* param)
{
    param->localPropertyIdxBuffer.freeBuffer();
    param->callTableParamBuffer.freeBuffer();
    param->actionNeedToCalcBuffer.freeBuffer();
}

bool UserResource::doBinarySearchToNameArray_(s32* value_idx, const char* name, u32* name_refs,
                                              u32 num_item)
{
    s32 a {0};
    s32 b {static_cast<s32>(num_item - 1)};

    while (a <= b) {
        const s32 m = (a + b) / 2;
        char* key_name {solveOffset<char>(name_refs[m])};

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

void UserResource::solveNeedObserveFlag_(UserResourceParam* param)
{
    ResUserHeader* user_header {param->userBinParam.pResUserHeader};
    ResAssetCallTable* asset_ctb {param->userBinParam.pResAssetCallTable};

    for (u32 i {0}; i < user_header->numCallTable; ++i) {
        s32 parent_index {asset_ctb[i].parentIndex};
        if (parent_index < 0 || asset_ctb[parent_index].flag.isOffBit(0))
            solveNeedObserveFlagImpl_(i, &asset_ctb[i], param, user_header);
    }
}

// NON-MATCHING
bool UserResource::solveNeedObserveFlagImpl_(u32 ctb_idx, ResAssetCallTable* asset_ctb,
                                             UserResourceParam* user_resource_param,
                                             ResUserHeader* user_header)
{
    CallTableParam* ctb_param {&user_resource_param->callTableParamBuffer[ctb_idx]};

    if (asset_ctb->flag.isOnBit(0)) {
        auto* container_param {ResourceUtil::getResContainerParam(*asset_ctb)};
        bool solved_need_observe {false};
        if (container_param != nullptr && container_param->childrenStartIndex >= 0 &&
            container_param->childrenEndIndex >= 0) {
            for (s32 i {container_param->childrenStartIndex};
                 i <= container_param->childrenEndIndex; ++i) {
                solved_need_observe = solveNeedObserveFlagImpl_(
                    i, &user_resource_param->userBinParam.pResAssetCallTable[i],
                    user_resource_param, user_header);
            }
        }

        if (asset_ctb->duration >= 0) {
            ctb_param->bitFlag.resetBit(1);
            return false;
        }

        if (solved_need_observe) {
            ctb_param->bitFlag.setBit(1);
            return true;
        }
    }
    else if (asset_ctb->duration >= 0) {
        if (ctb_param->bitFlag.isOffBit(0)) {
            ctb_param->bitFlag.resetBit(1);
            return false;
        }
    }

    ctb_param->bitFlag.setBit(1);
    return true;
}

ResAssetCallTable* UserResource::searchAssetAllResource(const char* name) const
{
    UserResourceParam* param {getParamWithSetupCheck()};
    if (param == nullptr)
        return nullptr;

    for (u64 i {0}; i < param->userBinParam.pResUserHeader->numCallTable; ++i) {
        ResAssetCallTable& asset_ctb {param->userBinParam.pResAssetCallTable[i]};
        char* key_name {solveOffset<char>(asset_ctb.keyNamePos)};

        if (strcmp(name, key_name) == 0)
            return &param->userBinParam.pResAssetCallTable[i];
    }

    return nullptr;
}

bool UserResource::hasGlobalPropertyTrigger() const
{
    UserResourceParam* param {getParamWithSetupCheck()};
    if (param == nullptr)
        return false;

    for (u32 i {0}; i < param->userBinParam.pResUserHeader->numResProperty; ++i) {
        if (param->userBinParam.pResPropertyTable[i].isGlobal)
            return true;
    }

    return false;
}

sead::DateTime* UserResource::getEditorSetupTime() const
{
    return nullptr;
}

void UserResource::checkAndAddErrorMultipleKeyByTrigger(
    [[maybe_unused]] const ResAssetCallTable& asset_ctb, [[maybe_unused]] TriggerType trigger_type)
{
}

bool UserResource::searchAssetCallTableByGuid(Locator* locator, s32 guid) const
{
    locator->reset();
    UserResourceParam* param {getParamWithSetupCheck()};
    if (param == nullptr)
        return false;

    for (u32 i {0}; i < param->userBinParam.pResUserHeader->numCallTable; ++i) {
        if (param->userBinParam.pResAssetCallTable[i].guid == guid) {
            locator->setAssetCallTable(&param->userBinParam.pResAssetCallTable[i]);
            return true;
        }
    }
    return false;
}

void UserResource::onSetupResourceParam_([[maybe_unused]] UserResourceParam* user_resource_param,
                                         [[maybe_unused]] const ParamDefineTable* pdt,
                                         [[maybe_unused]] sead::Heap* heap)
{
}
}  // namespace xlink2