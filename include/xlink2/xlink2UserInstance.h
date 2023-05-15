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
class ParamDefineTable;

class UserInstance {
public:
    class CreateArg {
    public:
        CreateArg(char const*, IUser*);
        CreateArg(const CreateArg& other);

    };

    class RebuildArg {
    public:
        RebuildArg() = default;
    };

    UserInstance(const CreateArg&, System*, User*, sead::Heap*);
    void destroy();

    u64 checkAndErrorCallInCalc(char const* /*unused*/, ...) const;
    void printLogFadeOrKill(Event const*, char const*, ...) const;
    void preCalc();
    void doOtameshiEmit_();
    void postCalc();
    void reset();
    void killAll();
    void sleep();
    void setIsActive(bool);
    void killAllOneTimeEvent();
    void clearAllEvent();

    void setupResource(sead::Heap*);
    bool isSetupRomInstanceParam() const;
    void setupInstanceParam(ResMode, sead::Heap*);

    void setupEditorInstanceParam();
    void changeInstanceParam(ResMode);

    void linkPropertyDefinitionToValueStruct(u32, PropertyDefinition const*);
    void saveEvent();
    void loadEventAndTriggerRestart();
    bool isInstanceParamValid() const;

    u64 getModelAssetConnection(u32) const;
    void searchAndEmitImpl(char const*, Handle*);

    u64 checkAndErrorCallWithoutSetup_(char const*, ...) const;
    void printLogSearchAsset_(bool, char const*, ...) const;
    void emitImpl(const Locator&, Handle*);

    void printLogEmitFailed(char const*, char const*, ...) const;
    bool isDebugLogEnable(DebugLogFlag) const;

    void checkAndBreakWhenEmit_(char const* /*unused*/);
    void freeEventIfFadeOrKillCalled();

    u64 getCurrentResActionIdx(s32) const;

    void* searchAsset(Locator*, char const*);
    void* searchAsset(Locator*, u32);
    bool searchAssetRecursive(Locator*, char const*);
    void* trySearchSwitchContainerRecursive(ResAssetCallTable const**, const ResAssetCallTable&);
    u64 searchEmittingEvent(Handle*, char const*) const;

    void changeAction(char const*, s32, s32);
    void changeAction(s32, s32, s32);
    void setActionFrame(s32, s32);
    void stopAction(s32);
    bool isCurrentActionNeedToObserve(s32) const;
    bool isCurrentActionNeedToCalc() const;

    void setPropertyValue(u32, s32);
    void setPropertyValue(u32, f32);
    bool isPropertyAssigned(u32) const;
    void setPropertyDefinition(u32, PropertyDefinition const*);

    char* getUserName() const;

    void makeDebugString(sead::BufferedSafeString*, const DebugOperationParam&) const;
    void makeDebugStringUserInformation(sead::BufferedSafeString*) const;
    void makeDebugStringAction(sead::BufferedSafeString*, sead::SafeString const&) const;
    void makeDebugStringLocalProperty(sead::BufferedSafeString*, sead::SafeString const&) const;
    void setDebugLogFlag(sead::BitFlag32);

    void setRootMtx(sead::Matrix34f const*);
    void setRootPos(sead::Vector3f const*);

    void setRandomHistory(u32, u32);
    u32 searchRandomHistory(u32) const;

    void updateSortKey();
    u64 getPosForSort() const;
    u32 getSortKey() const;
    void getRootMtxForDrawText(sead::Matrix34f*);

    void printLogContainerSelect(Event const&, char const*, ...) const;
    void printLogEmitFailed(Event const&, char const*, ...) const;

    char* getContainerTypeName(ResAssetCallTable const&) const;

    void fadeOrKillOtameshi(bool);

    void rebuild(const RebuildArg&);

    virtual void makeDebugStringEvent(sead::BufferedSafeString*, const sead::SafeString&) const = 0;
    virtual ~UserInstance();
    virtual u32 getDefaultGroup() const;
    virtual void onPostCalc_() = 0;
    virtual void onReset_();
    virtual void onDestroy_() = 0;
    virtual void allocInstanceParam_(sead::Heap*) = 0;
    virtual void freeInstanceParam_(UserInstanceParam*, ResMode);
    virtual void onSetupInstanceParam_(ResMode /*unused*/, sead::Heap* /*unused*/);
    virtual void initModelAssetConnection_(ResMode, ParamDefineTable const*, sead::Heap*) = 0;
    virtual u32 doEventActivatingCallback_(Locator const& /*unused*/);
    virtual void doEventActivatedCallback_(Locator const& /*unused*/, Event* /*unused*/);

    User* getUser() const { return mUser; };

protected:
    sead::OffsetList<Event> mEventList;
    sead::SafeArray<UserInstanceParam*, 2> mParamsByResMode;
    User* mUser;
    IUser* mIUser;
    sead::Matrix34f* mRootMtx;
    u8 _0x48;
    sead::Vector3f* mRootPos;
    sead::Vector3f* mScale;
    f32 mSortKey;
    u64 mValueChangedBitfield;
    f32* mPropertyValueArray;
    TriggerCtrlMgr mTriggerCtrlMgr;
    void* _0x98;
    u8 _0xA0[0x30];
    u8 _0xD0;
    void* _3;
    void* _4;
    void* _5;
};
}  // namespace xlink2