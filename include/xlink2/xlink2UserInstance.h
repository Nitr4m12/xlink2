#pragma once

#include <math/seadVector.h>

#include "xlink2/xlink2DebugLogFlag.h"
#include "xlink2/xlink2DebugOperationParam.h"
#include "xlink2/xlink2TriggerCtrlMgr.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserInstanceParam.h"

namespace xlink2 {
class Event;
class ParamDefineTable;
class Handle;
class Locator;
class IUser;

class UserInstance {

public:
    class CreateArg {
    public:
        CreateArg(const char*, IUser*);
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

    bool checkAndErrorCallInCalc(const char* /*unused*/, ...) const;
    void printLogFadeOrKill(const Event*, const char*, ...) const;
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

    void linkPropertyDefinitionToValueStruct(u32, const PropertyDefinition*);

    void saveEvent();
    void loadEventAndTriggerRestart();
    bool isInstanceParamValid() const;

    ModelAssetConnection* getModelAssetConnection(u32) const;
    void searchAndEmitImpl(const char*, Handle*);

    bool checkAndErrorCallWithoutSetup_(const char*, ...) const;
    void printLogSearchAsset_(bool, const char*, ...) const;
    void emitImpl(const Locator&, Handle*);

    void printLogEmitFailed(const char*, const char*, ...) const;
    bool isDebugLogEnable(DebugLogFlag) const;

    void checkAndBreakWhenEmit_(const char* /*unused*/);
    
    void freeEventIfFadeOrKillCalled();

    s32 getCurrentResActionIdx(s32) const;

    bool searchAsset(Locator*, const char*);
    bool searchAsset(Locator*, u32);
    bool searchAssetRecursive(Locator*, const char*);
    void* trySearchSwitchContainerRecursive_(const ResAssetCallTable**, const ResAssetCallTable&);
    u64 searchEmittingEvent(Handle*, const char*) const;

    void changeAction(const char*, s32, s32);
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
    void makeDebugStringAction(sead::BufferedSafeString*, const sead::SafeString&) const;
    void makeDebugStringLocalProperty(sead::BufferedSafeString*, const sead::SafeString&) const;
    void setDebugLogFlag(sead::BitFlag32);

    void setRootMtx(const sead::Matrix34f* root_mtx);
    void setRootPos(const sead::Vector3f* root_pos);

    void setRandomHistory(u32, u32);
    u32 searchRandomHistory(u32) const;

    void updateSortKey();
    u64 getPosForSort() const;
    f32 getSortKey() const;
    void getRootMtxForDrawText(sead::Matrix34f*);

    void printLogContainerSelect(const Event&, const char*, ...) const;
    void printLogEmitFailed(const Event&, const char*, ...) const;

    const sead::SafeString* getContainerTypeName(const ResAssetCallTable&) const;

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
    virtual void initModelAssetConnection_(ResMode, const ParamDefineTable*, sead::Heap*) = 0;
    virtual bool doEventActivatingCallback_(const Locator& /*unused*/);
    virtual void doEventActivatedCallback_(const Locator& /*unused*/, Event* /*unused*/);

    User* getUser() const { return mUser; };
    UserResource* getUserResource() const { return mUser->getUserResource(); }

    sead::BitFlag8 getBitFlag() const { return mBitFlag; };
    UserInstanceParam* getParam() const { return mParams[mBitFlag & 1]; };

    const IUser* getIUser() const { return mIUser; };

    const sead::OffsetList<Event>* getEventList() const { return &mEventList; }

    void updateGlobalPropertyTriggerCtrl() 
    {
        if (mBitFlag.isOffBit(1))
            mTriggerCtrlMgr.updateGlobalPropertyTriggerCtrl();
    }

protected:
    friend TriggerCtrlMgr;

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