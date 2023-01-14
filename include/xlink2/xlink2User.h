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
    char* mName;
    void* _1;
    char* mUserName;
    UserResource* mUserResource;
    User* mUser1;
    User* mUser2;
    u32 _6;
    s32 mUserInstancePos;
    sead::Heap* mHeap;
    u32 _8;
    u16 _9;
    s16 mResActionSlotNum;
    ResActionSlot* mResActionSlotTable;
};
}  // namespace xlink2