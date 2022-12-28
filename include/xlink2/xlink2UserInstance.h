#pragma once

#include "math/seadMatrix.h"
#include "xlink2/xlink2.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2User.h"

namespace xlink2 {
class UserInstanceParam;
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
    u64 checkAndErrorCallInCalc(char const*, ...) const;
    u64 checkAndErrorCallWithoutSetup(char const*, ...) const;

    void clearAllEvent();
    void destroy();
    void doEventActivatedCallback(Locator const&, Event*);
    void doEventActivatingCallback(Locator const&);
    void doOtameshiEmit();

    void emitImpl(Locator const&, Handle*);
    void fadeOrKillOtameshi(bool);
    void freeEventIfFadeOrKillCalled();
    void freeInstanceParam(UserInstanceParam*, ResMode);

    void getContainerTypeName(ResAssetCallTable const&) const;
    void getCurrentResActionIdx(s32) const;
    void getDefaultGroup() const;
    u64 getModelAssetConnection(u32) const;
    u64 getPosForSort() const;
    void getRootMtxForDrawText(sead::Matrix34f*);
    u32 getSortKey() const;
    char* getUserName() const;

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

    void onReset();

    ResMode onSetupInstanceParam(ResMode, sead::Heap*);

    void postCalc();
    void preCalc();

    void printLogContainerSelect(Event const&, char const*, ...) const;
    void printLogEmitFailed(char const*, char const*, ...) const;
    void printLogEmitFailed(Event const&, char const*, ...) const;
    void printLogFadeOrKill(Event const*, char const*, ...) const;
    void* printLogSearchAsset(bool, char const*, ...) const;

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
};

class HandleELink;
class UserInstanceELink {
    virtual ~UserInstanceELink();

public:
    UserInstanceELink(UserInstance::CreateArg const&, System*, User*, sead::Heap*);

    void allocInstanceParam(sead::Heap*);
    void emit(Locator const&);
    void emit(Locator const&, HandleELink*);
    void fadeIfLoopEffect();
    void freeInstanceParam(UserInstanceParam*, ResMode);

    UserInstanceELink getDefaultGroup() const;
    u64 getResourceAccessor() const;
    u64 getResourceELink() const;

    void initModelAssetConnection(ResMode, ParamDefineTable const*, sead::Heap*);

    void makeDebugStringEvent(sead::BufferedSafeString*, sead::SafeString const&) const;

    void onDestroy();
    void onPostCalc();
    void onReset();
    void onSetupInstanceParam(ResMode, sead::Heap*);

    void searchAndEmit(char const*);
    void searchAndEmit(char const*, HandleELink*);
    void searchAndHold(char const*);
    void searchAndHold(char const*, HandleELink*);

private:
};

class ArrangeGroupParam;
class HandleSLink;
class ResourceAccessorSLink;
class UserInstanceSLink {
    virtual ~UserInstanceSLink();

public:
    class AssetLimiter {
        virtual ~AssetLimiter();

    public:
        AssetLimiter(s32, sead::Heap*);
        void initialize(s32, char const*, ArrangeGroupParam const&);

        void append(Event const&, ResourceAccessorSLink const&, User*);
        void clear();
        void limit();

    private:
    };
    class CreateArgSLink {
    public:
        CreateArgSLink(char const*, IUser*);
        explicit CreateArgSLink(UserInstance::CreateArg const&);
        CreateArgSLink(CreateArgSLink const&);

    private:
    };
    UserInstanceSLink(CreateArgSLink const&, System*, User*, sead::Heap*);

    void allocEmitter(sead::Heap*);
    void allocInstanceParam(sead::Heap*);
    void doEventActivatedCallback(Locator const&, Event*);
    void doEventActivatingCallback(Locator const&);

    void emit(Locator const&);
    void emit(Locator const&, HandleSLink*);
    void emit(ResAssetCallTable const&);
    void emit(ResAssetCallTable const&, HandleSLink*);

    void fadeIfLoopSound();
    // void freeEmitter(aal::Emitter*)
    void freeInstanceParam(UserInstanceParam*, ResMode);

    u64 getResourceAccessor() const;
    u64 getResourceSLink() const;
    s32 getSoundSourceNum() const;

    void initModelAssetConnection(ResMode, ParamDefineTable const*, sead::Heap*);

    void makeDebugStringEvent(sead::BufferedSafeString*, sead::SafeString const&) const;

    void onDestroy();
    void onPostCalc();
    void onSetupInstanceParam(ResMode, sead::Heap*);

    void searchAndEmit(char const*);
    void searchAndEmit(char const*, HandleSLink*);
    void searchAndHold(char const*);
    void searchAndHold(char const*, HandleSLink*);

    // void setAssetInfoReader(aal::IAssetInfoReadable*);

    void setupEmitter(ResAssetCallTable const&);
    void stopAllEvent(s32);

private:
};
}  // namespace xlink2