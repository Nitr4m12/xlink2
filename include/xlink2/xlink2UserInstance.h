#pragma once

#include "math/seadMatrix.h"
#include "xlink2/xlink2DebugLogFlag.h"
#include "xlink2/xlink2DebugOperationParam.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2Handle.h"
#include "xlink2/xlink2IUser.h"
#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2TriggerCtrlMgr.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserInstanceParam.h"

namespace xlink2 {
class Event;
class System;
class User;

class UserInstance {
    virtual ~UserInstance();

public:
    class CreateArg {
    public:
        CreateArg(char const*, IUser*);
    };

    class RebuildArg {
    public:
        RebuildArg() = default;
    };

    UserInstance(CreateArg const&, System*, User*, sead::Heap*);

    void changeAction(char const*, s32, s32);
    void changeAction(s32, s32, s32);
    void changeInstanceParam(ResMode);

    void checkAndBreakWhenEmit(char const*);
    u64 checkAndErrorCallInCalc(char const* /*unused*/, ...) const;
    u64 checkAndErrorCallWithoutSetup(char const*, ...) const;

    void clearAllEvent();
    void destroy();
    void doEventActivatedCallback_(Locator const& /*unused*/, Event* /*unused*/);
    u32 doEventActivatingCallback_(Locator const& /*unused*/);
    void doOtameshiEmit();

    void emitImpl(Locator const&, Handle*);
    void fadeOrKillOtameshi(bool);
    void freeEventIfFadeOrKillCalled();
    void freeInstanceParam(UserInstanceParam*, ResMode);

    void getContainerTypeName(ResAssetCallTable const&) const;
    void getCurrentResActionIdx(s32) const;
    u32 getDefaultGroup() const;
    u64 getModelAssetConnection(u32) const;
    u64 getPosForSort() const;
    void getRootMtxForDrawText(sead::Matrix34f*);
    u32 getSortKey() const;
    char* getUserName() const;

    User* getUser() const { return mUser; };

    bool isCurrentActionNeedToCalc() const;
    bool isCurrentActionNeedToObserve(s32) const;
    bool isDebugLogEnable(DebugLogFlag) const;
    bool isInstanceParamValid() const;
    bool isPropertyAssigned(u32) const;
    bool isSetupRomInstanceParam() const;

    void killAll();
    void killAllOneTimeEvent();

    void linkPropertyDefinitionToValueStruct(u32, PropertyDefinition const*);
    void loadEventAndTriggerRestart();

    void makeDebugString(sead::BufferedSafeString*, DebugOperationParam const&) const;
    void makeDebugStringAction(sead::BufferedSafeString*, sead::SafeString const&) const;
    void makeDebugStringLocalProperty(sead::BufferedSafeString*, sead::SafeString const&) const;
    void makeDebugStringUserInformation(sead::BufferedSafeString*) const;

    void onReset_();
    void onSetupInstanceParam_(ResMode /*unused*/, sead::Heap* /*unused*/);

    void postCalc();
    void preCalc();

    void printLogContainerSelect(Event const&, char const*, ...) const;
    void printLogEmitFailed(char const*, char const*, ...) const;
    void printLogEmitFailed(Event const&, char const*, ...) const;
    void printLogFadeOrKill(Event const*, char const*, ...) const;
    void printLogSearchAsset_(bool, char const*, ...) const;

    void rebuild(RebuildArg const&);

    void reset();
    void saveEvent();
    void searchAndEmitImpl(char const*, Handle*);
    void* searchAsset(Locator*, char const*);
    void* searchAsset(Locator*, u32);
    bool searchAssetRecursive(Locator*, char const*);
    u64 searchEmittingEvent(Handle*, char const*) const;
    u32 searchRandomHistory(u32) const;

    void setActionFrame(s32, s32);
    void setDebugLogFlag(sead::BitFlag32);
    void setIsActive(bool);
    void setPropertyDefinition(u32, PropertyDefinition const*);
    void setPropertyValue(u32, s32);
    void setPropertyValue(u32, f32);
    void setRandomHistory(u32, u32);
    void setRootMtx(sead::Matrix34f const*);
    void setRootPos(sead::Vector3f const*);

    void setupEditorInstanceParam();
    void setupInstanceParam(ResMode, sead::Heap*);
    void setupResource(sead::Heap*);

    void sleep();
    void stopAction(s32);

    void* trySearchSwitchContainerRecursive(ResAssetCallTable const**, ResAssetCallTable const&);

    void updateSortKey();

protected:
    sead::OffsetList<Event> mEventList;
    sead::SafeArray<UserInstanceParam*, 2> mParamsByResMode;
    User* mUser;
    IUser* mIUser;
    sead::Matrix34f* mRootMtx;
    u8 _0;
    sead::Vector3f* mRootPos;
    sead::Vector3f* mScale;
    f32 mSortKey;
    u64 mValueChangedBitfield;
    f32* mPropertyValueArray;
    TriggerCtrlMgr mTriggerCtrlMgr;
    void* _1;
    u8 _2[48];
    bool mIsActive;
    void* _3;
    void* _4;
    void* _5;
};
}  // namespace xlink2