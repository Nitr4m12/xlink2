#include <math/seadMathCalcCommon.h>

#include "xlink2/xlink2User.h"

namespace xlink2 {

System* User::getSystem() const 
{
    return mUserResource->getSystem();
}

s32 User::calcNumActiveInstance() const
{
    s32 num_active_instance {0};
    for (auto& user_instance : mUserInstanceList) {
        num_active_instance += user_instance.getBitFlag().isOffBit(1);
    }

    return num_active_instance;
}

u64 User::searchPropertyIndex(const char* name) const 
{
    u16 num_local_prop = mNumLocalProp;
    if (num_local_prop != 0) {
        for (u64 i{0}; i < num_local_prop; ++i) {
            PropertyDefinition* property_definition = mPropertyDefinitionTable[i];
            if (property_definition != nullptr) {
                sead::FixedSafeString<64>* prop_name = property_definition->getPropertyName();
                int result = strcmp(name, prop_name->getBuffer());
                if (result == 0)
                    return i;
            }
        }
        num_local_prop = mNumLocalProp;
    }

    return 0xFFFFFFFF;
}

void User::changeEditorResource(EditorResourceParam* editor_param, sead::Heap* heap) 
{
    mUserResource->setupEditorResourceParam_(editor_param, heap);
    mUserResource->setResMode(ResMode::Editor);
    for (auto& user_instance : mUserInstanceList) {
        user_instance.setupEditorInstanceParam();
        user_instance.changeInstanceParam(ResMode::Editor);
    }
}

void User::rollbackToRomResource()
{
    mUserResource->setResMode(ResMode::Rom);
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
            min_sort_key_instance = &user_instance;;
        }
    }
    return min_sort_key_instance;
}

void User::updateSortKey() 
{
    for (auto& user_instance : mUserInstanceList)
        user_instance.updateSortKey();
}

void User::setDebugDisable(bool) {}

void User::beginOtameshi() 
{
    for (auto& user_instance : mUserInstanceList) {
        user_instance.fadeOrKillOtameshi(true);
        user_instance.freeEventIfFadeOrKillCalled();
    }
}
}  // namespace xlink2
