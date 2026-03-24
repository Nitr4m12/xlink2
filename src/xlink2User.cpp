#include <math/seadMathCalcCommon.h>

#include "xlink2/xlink2User.h"
#include "xlink2/xlink2PropertyDefinition.h"
#include "xlink2/xlink2UserResource.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
User::User(const char* user_name, sead::Heap* heap, System* system, u32 i1)
    : mUserName(user_name), mpHeap(heap), _0x40(i1)
{
    mUserInstanceList.initOffset(0xd8);
    if (system->getMutexSize() > 0) {
        s32 buffer_size = static_cast<s32>(std::strlen(user_name));
        char* user_name_buffer {new(heap) char[buffer_size + 1]};
        std::strncpy(user_name_buffer, user_name, buffer_size);
        user_name_buffer[buffer_size] = sead::SafeString::cNullChar;

        mUserName = user_name_buffer;
        mBitFlag.setBit(1);
    }

    mpUserResource = system->createUserResource(this, heap);
}

User::~User()
{
    delete[] mActionSlotNameTable;

    if (mpPropertyDefinitionTable != nullptr) {
        delete[] mpPropertyDefinitionTable;
        mpPropertyDefinitionTable = nullptr;
    }

    mNumLocalProp = 0;

    if (mpUserResource != nullptr) {
        mpUserResource->destroy();
        delete mpUserResource;
        mpUserResource = nullptr;
    }

    if (mBitFlag.isOnBit(1))
        delete mUserName;
}

System* User::getSystem() const 
{
    return mpUserResource->getSystem();
}

s32 User::calcNumActiveInstance() const
{
    s32 num_active_instance {0};
    for (auto& user_instance : mUserInstanceList)
        num_active_instance += user_instance.getBitFlag().isOffBit(1);
    

    return num_active_instance;
}

void User::setActionSlot(u32 total_action_slots, const char** slot_names)
{
    mNumActionSlot = total_action_slots;
    if (mNumActionSlot > 0)
        mActionSlotNameTable = slot_names;
}

s32 User::searchActionSlotPos(const char* name) const
{
    if (mNumActionSlot > 0) {
        for (s32 i {0}; i < mNumActionSlot; ++i) {
            const char* action_slot_name {mActionSlotNameTable[i]}; 
            if (strcmp(action_slot_name, name) == 0)
                return i & -1;
        }
    }

    return -1;
}

u32 User::searchPropertyIndex(const char* name) const 
{
    if (mNumLocalProp != 0) {
        for (u32 i{0}; i < mNumLocalProp; ++i) {
            PropertyDefinition* property_definition = mpPropertyDefinitionTable[i];
            if (property_definition != nullptr) {
                const sead::FixedSafeString<64>* prop_name = property_definition->getPropertyName();
                if (strcmp(name, prop_name->cstr()) == 0)
                    return i;
            }
        }
    }

    return -1;
}

void User::changeEditorResource(EditorResourceParam* editor_param, sead::Heap* heap) 
{
    mpUserResource->setupEditorResourceParam(editor_param, heap);
    mpUserResource->setResMode(ResMode::Editor);
    for (auto& user_instance : mUserInstanceList) {
        user_instance.setupEditorInstanceParam();
        user_instance.changeInstanceParam(ResMode::Editor);
    }
}

void User::rollbackToRomResource()
{
    mpUserResource->setResMode(ResMode::Rom);
    for (auto& user_instance : mUserInstanceList)
        user_instance.changeInstanceParam(ResMode::Rom);
}

void User::saveEvent() 
{
    for (auto& user_instance : mUserInstanceList)
        user_instance.saveEvent();
}

void User::loadEventAndTriggerRestart() 
{
    for (auto& user_instance : mUserInstanceList)
        user_instance.loadEventAndTriggerRestart();
}

void User::killAll() 
{
    for (auto& user_instance : mUserInstanceList)
        user_instance.killAll();
}

UserInstance* User::getLeaderInstance() const
{
    return mUserInstanceList.front();
}

f32 User::getMinSortKey() const
{
    f32 min_sort_key {sead::MathCalcCommon<f32>::infinity()};
    for (auto& user_instance : mUserInstanceList) {
        f32 sort_key = user_instance.getSortKey();
        sort_key = sead::MathCalcCommon<f32>::min(sort_key, min_sort_key);

        min_sort_key = sort_key;
    }
    return min_sort_key;
}

UserInstance* User::getMinSortKeyInstance()
{
    f32 min_sort_key {sead::MathCalcCommon<f32>::infinity()};
    UserInstance* min_sort_key_instance {};
    for (auto& user_instance : mUserInstanceList) {
        f32 sort_key = user_instance.getSortKey();
        if (sort_key < min_sort_key) {
            min_sort_key = sort_key;
            min_sort_key_instance = &user_instance;
        }
    }
    return min_sort_key_instance;
}

void User::updateSortKey() 
{
    for (auto& user_instance : mUserInstanceList)
        user_instance.updateSortKey();
}

void User::setDebugDisable([[maybe_unused]] bool debug_disable) {}

void User::beginOtameshi() 
{
    for (auto& user_instance : mUserInstanceList) {
        user_instance.fadeOrKillOtameshi(true);
        user_instance.freeEventIfFadeOrKillCalled();
    }
}

// NON-MATCHING: getMinSortKeyInstance not inlining properly
bool User::requestOtameshi() 
{
    updateSortKey();
    return getMinSortKeyInstance() != nullptr;
}
}  // namespace xlink2
