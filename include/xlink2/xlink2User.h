#pragma once

#include "heap/seadHeap.h"
#include "math/seadMatrix.h"
#include "xlink2/xlink2EditorResourceParam.h"
#include "xlink2/xlink2PropertyDefinition.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2ToolConnectionContext.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class User {
    virtual ~User();

public:
    // User(char const*, sead::Heap*, System*, u32);

    void beginOtameshi();
    s32 calcNumActiveInstance() const;
    void changeEditorResource(EditorResourceParam*, sead::Heap*);
    void createPropertyDefinitionTable(u32);
    void createPropertyDefinitionTable(u32, PropertyDefinition const**);

    u64 getLeaderInstance() const;
    f32 getMinSortKey() const;
    // UserInstance* getMinSortKeyInstance();
    void getSystem() const;

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
};
}  // namespace xlink2