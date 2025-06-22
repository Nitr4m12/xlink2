#pragma once

#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>

#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2DebugLogFlag.h"
#include "xlink2/xlink2DebugOperationParam.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2Handle.h"
#include "xlink2/xlink2IUser.h"
#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2ModelAssetConnection.h"
#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2TriggerCtrlMgr.h"
#include "xlink2/xlink2PropertyValueType.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserInstanceParam.h"

namespace xlink2 {
class Event;
class System;
class User;
class ParamDefineTable;

class UserInstance {
public:
    class CreateArg {
    public:
        CreateArg(char const*, IUser*);
        CreateArg(const CreateArg& other);

        char* name;
        IUser* iUser;
        BoneMtx rootMtx;
        sead::Vector3f* rootPos;
        sead::Vector3f* scale;
        s32 actionSlotCount;
        s32 localPropertyCount;
        char* actionSlotNames;
    };

    class RebuildArg {
    public:
        RebuildArg() = default;

        BoneMtx rootMtx;
        sead::Vector3f* rootPos;
        sead::Vector3f* _18;
    };

    enum class ParamType : u8 {
        Normal,
        Editor
    };

    UserInstance(const CreateArg&, System*, User*, sead::Heap*);
    void destroy();

    bool checkAndErrorCallInCalc(char const* /*unused*/, ...) const;
    void printLogFadeOrKill(Event const*, char const*, ...) const;
    void preCalc();
    void doOtameshiEmit_();
    void postCalc();

    void reset(); 
    void killAll();
    void sleep();

    void setIsActive(bool is_active);
    void killAllOneTimeEvent();
    void clearAllEvent();

    void setupResource(sead::Heap* heap);
    bool isSetupRomInstanceParam_() const;

    void setupInstanceParam_(ResMode, sead::Heap*);
    void setupEditorInstanceParam();
    void changeInstanceParam(ResMode);

    void linkPropertyDefinitionToValueStruct(u32, PropertyDefinition const*);

    void saveEvent();
    void loadEventAndTriggerRestart();
    bool isInstanceParamValid() const;

    ModelAssetConnection* getModelAssetConnection(u32) const;
    void searchAndEmitImpl(char const*, Handle*);

    bool checkAndErrorCallWithoutSetup_(char const*, ...) const;
    void printLogSearchAsset_(bool, char const*, ...) const;
    void emitImpl(const Locator&, Handle*);

    void printLogEmitFailed(char const*, char const*, ...) const;
    bool isDebugLogEnable(DebugLogFlag) const;

    void checkAndBreakWhenEmit_(char const* /*unused*/);
    
    void freeEventIfFadeOrKillCalled();

    u64 getCurrentResActionIdx(s32) const;

    bool searchAsset(Locator*, char const*);
    bool searchAsset(Locator*, u32);
    bool searchAssetRecursive(Locator*, const char*);
    void* trySearchSwitchContainerRecursive_(ResAssetCallTable const**, const ResAssetCallTable&);
    u64 searchEmittingEvent(Handle*, char const*) const;

    void changeAction(char const*, s32, s32);
    void changeAction(s32, s32, s32);
    void setActionFrame(s32, s32);
    void stopAction(s32);
    bool isCurrentActionNeedToObserve(s32) const;
    bool isCurrentActionNeedToCalc() const;

    void setPropertyValue(u32 idx, s32 value);
    void setPropertyValue(u32 idx, f32 value);
    bool isPropertyAssigned(u32 idx) const;
    void setPropertyDefinition(u32, const PropertyDefinition*);

    char* getUserName() const;

    void makeDebugString(sead::BufferedSafeString*, const DebugOperationParam&) const;
    void makeDebugStringUserInformation(sead::BufferedSafeString*) const;
    void makeDebugStringAction(sead::BufferedSafeString*, sead::SafeString const&) const;
    void makeDebugStringLocalProperty(sead::BufferedSafeString*, sead::SafeString const&) const;
    void setDebugLogFlag(sead::BitFlag32);

    void setRootMtx(const sead::Matrix34f* root_mtx);
    void setRootPos(const sead::Vector3f* root_pos);

    void setRandomHistory(u32, u32);
    u32 searchRandomHistory(u32) const;

    void updateSortKey();
    u64 getPosForSort() const;
    f32 getSortKey() const;
    void getRootMtxForDrawText(sead::Matrix34f*);

    void printLogContainerSelect(Event const&, char const*, ...) const;
    void printLogEmitFailed(Event const&, char const*, ...) const;

    const sead::SafeString* getContainerTypeName(ResAssetCallTable const&) const;

    void fadeOrKillOtameshi(bool kill);

    void rebuild(const RebuildArg&);

    virtual void makeDebugStringEvent(sead::BufferedSafeString*, const sead::SafeString&) const = 0;
    virtual ~UserInstance();
    virtual u32 getDefaultGroup() const;
    virtual void onPostCalc_() = 0;
    virtual void onReset_();
    virtual void onDestroy_() = 0;
    virtual UserInstanceParam* allocInstanceParam_(sead::Heap*) = 0;
    virtual void freeInstanceParam_(UserInstanceParam*, ResMode);
    virtual void onSetupInstanceParam_(ResMode /*unused*/, sead::Heap* /*unused*/);
    virtual void initModelAssetConnection_(ResMode, ParamDefineTable const*, sead::Heap*) = 0;
    virtual bool doEventActivatingCallback_(Locator const& /*unused*/);
    virtual void doEventActivatedCallback_(Locator const& /*unused*/, Event* /*unused*/);

    User* getUser() const { return mUser; };
    sead::BitFlag8 getBitFlag() const { return mBitFlag; };
    UserInstanceParam* getParam() const { return mParams[mBitFlag & 1]; };

    bool unkCheck();

protected:
    sead::OffsetList<Event> mEventList;
    sead::SafeArray<UserInstanceParam*, 2> mParams;
    User* mUser;
    IUser* mIUser;
    BoneMtx mRootMtx;
    const sead::Vector3f* mRootPos;
    const sead::Vector3f* mScale; // Just a guess
    f32 mSortKey;
    sead::BitFlag64 mValueChangedBitfield;
    PropertyValueType* mPropertyValueArray;
    TriggerCtrlMgr mTriggerCtrlMgr;
    void* _0x98;
    u8 _0xA0[0x30];
    sead::BitFlag8 mBitFlag;
};
static_assert(sizeof(UserInstance) == 0xd8, "xlink2::UserInstance size mismatch");
}  // namespace xlink2