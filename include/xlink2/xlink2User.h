#pragma once

#include "heap/seadHeap.h"
#include "math/seadMatrix.h"
#include "xlink2/xlink2EditorResourceParam.h"
#include "xlink2/xlink2PropertyDefinition.h"
#include "xlink2/xlink2ResActionSlot.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2ToolConnectionContext.h"
#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2UserResource.h"

namespace xlink2 {
class System;
class UserResource;
class UserInstance;

class User {
public:
    User(char const*, sead::Heap*, System*, u32);
    ~User();
    void beginOtameshi();
    s32 calcNumActiveInstance() const;
    void changeEditorResource(EditorResourceParam*, sead::Heap*);
    void createPropertyDefinitionTable(u32);
    void createPropertyDefinitionTable(u32, PropertyDefinition const**);

    u64 getLeaderInstance() const;
    f32 getMinSortKey() const;
    UserInstance* getMinSortKeyInstance();
    System* getSystem() const;

    char* getUserName() { return mUserName; }
    UserResource* getUserResource() { return mUserResource; }

    void killAll();
    void loadEventAndTriggerRestart();

    bool requestOtameshi();
    void rollbackToRomResource();

    void saveEvent();

    u64 searchActionSlotPos(char const*) const;
    u64 searchPropertyIndex(char const*) const;

    void setActionSlot(u32, char const**);
    void setDebugDisable(bool);
    void setPropertyDefinition(u32, PropertyDefinition const*);

    void updateSortKey();

private:
    void* _0;
    void* _1;
    char* mUserName;
    UserResource* mUserResource;
    sead::SafeArray<UserInstance*, 2> mUserInstanceArray;
    u32 _6;
    s32 _7;
    sead::Heap* mHeap;
    u32 _8;
    u16 mPropertyDefinitionTableNum;
    s16 mResActionSlotNum;
    PropertyDefinition** mPropertyDefinitionTable;
    ResActionSlot* mResActionSlot;
    u8 _11;
};
}  // namespace xlink2