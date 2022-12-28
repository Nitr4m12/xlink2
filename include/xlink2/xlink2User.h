#pragma once

#include "math/seadMatrix.h"
#include "xlink2/xlink2.h"
#include "xlink2/xlink2ResourceParamCreator.h"

namespace xlink2 {
class IUser {
public:
    u32 getActionName(int, int) const;
    u64 getActionSlotName(int) const;
    u64 getBoneWorldMtx(char const*, sead::Matrix34f*) const;
    u64 getDebugDrawCamera() const;
    u64 getDebugDrawProjection() const;
    u64 getDebugUserName() const;
    u64 getMtxCorrectingDrawBone() const;
    u64 getNumAction(int) const;
    void getReservedAssetName(ToolConnectionContext*) const;
    u64 getUserInformation();

private:
};

class User {
    virtual ~User();

public:
    User(char const*, sead::Heap*, System*, u32);

    void beginOtameshi();
    s32 calcNumActiveInstance() const;
    void changeEditorResource(EditorResourceParam*, sead::Heap*);
    void createPropertyDefinitionTable(u32);
    void createPropertyDefinitionTable(u32, PropertyDefinition const**);

    u64 getLeaderInstance() const;
    f32 getMinSortKey() const;
    UserInstance* getMinSortKeyInstance();
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