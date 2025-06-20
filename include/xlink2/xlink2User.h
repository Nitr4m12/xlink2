#pragma once

#include <container/seadOffsetList.h>
#include <heap/seadHeap.h>

#include "xlink2/xlink2EditorResourceParam.h"
#include "xlink2/xlink2PropertyDefinition.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2UserResource.h"

namespace xlink2 {
class UserResource;
class UserInstance;

class User {
public:
    User(char const*, sead::Heap*, System*, u32);
    ~User();

    System* getSystem() const;

    s32 calcNumActiveInstance() const;

    void setActionSlot(u32 total_action_slot, const char** slot_names);
    s32 searchActionSlotPos(char const*) const;
    
    void createPropertyDefinitionTable(u32);
    void createPropertyDefinitionTable(u32, PropertyDefinition const**);
    void setPropertyDefinition(u32, PropertyDefinition const*);
    u32 searchPropertyIndex(const char* name) const;
    
    void changeEditorResource(EditorResourceParam*, sead::Heap*);
    void rollbackToRomResource();

    void saveEvent();
    void loadEventAndTriggerRestart();
    void killAll();

    UserInstance* getLeaderInstance() const;
    
    f32 getMinSortKey() const;
    UserInstance* getMinSortKeyInstance();
    void updateSortKey();

    void setDebugDisable(bool);

    void beginOtameshi();
    bool requestOtameshi();

    char* getUserName() { return mUserName; }
    UserResource* getUserResource() { return mUserResource; }
    u16 getPropertyDefinitionTableNum() const { return mNumLocalProp; }
private:
    void* _0;
    void* _1;
    char* mUserName;
    UserResource* mUserResource;
    sead::OffsetList<UserInstance> mUserInstanceList;
    sead::Heap* mHeap;
    u32 _8;
    u16 mNumLocalProp;
    s16 mActionSlotNum;
    PropertyDefinition** mPropertyDefinitionTable;
    const char** mActionSlotNames;
    u8 _11;
};
static_assert(sizeof(User) == 0x60, "Wrong size for 'xlink2::User'");

}  // namespace xlink2
