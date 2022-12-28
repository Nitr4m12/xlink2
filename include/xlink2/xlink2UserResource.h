#pragma once

#include "xlink2/xlink2.h"
#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2ResourceParamCreator.h"

namespace xlink2 {
class UserResourceParam;
class UserResource {
    virtual ~UserResource();

public:
    explicit UserResource(User*);

    void checkAndAddErrorMultipleKeyByTrigger(ResAssetCallTable const&, TriggerType);
    void destroy();

    u32 doBinarySearchAsset(char const*, TriggerType) const;
    u64 doBinarySearchToNameArray(s32*, char const*, u32*, u32);
    void freeResourceParam(UserResourceParam*);

    u64 getActionTriggerTableItem(s32) const;
    u64 getAlwaysTriggerTableItem(s32) const;
    u64 getAssetCallTableItem(s32) const;
    u64 getEditorSetupTime() const;
    u64 getPropertyTriggerTableItem(s32) const;
    u64 getUserHeader() const;

    u64 hasGlobalPropertyTrigger() const;

    void onSetupResourceParam(UserResourceParam*, ParamDefineTable const*, sead::Heap*);

    u64 searchAssetAllResource(char const*) const;
    u64 searchAssetCallTableByGuid(Locator*, s32) const;
    u64 searchAssetCallTableByHash(Locator*, u32) const;
    u64 searchAssetCallTableByName(Locator*, char const*) const;
    u64 searchAssetCallTableByName(char const*) const;

    void setup(sead::Heap*);
    void setupEditorResourceParam(EditorResourceParam*, sead::Heap*);
    void setupResourceParam(UserResourceParam*, ResUserHeader*, CommonResourceParam const*, ParamDefineTable const*, sead::Heap*);
    void setupRomResourceParam(sead::Heap*);

    void solveNeedObserveFlag(UserResourceParam*);
    u64 solveNeedObserveFlagImpl(u32, ResAssetCallTable*, UserResourceParam*, ResUserHeader*);
private:
};

class UserResourceParamELink;
class UserResourceELink {
    virtual ~UserResourceELink();

public:
    UserResourceELink(User*, sead::Heap*);

    void allocResourceParam(sead::Heap);
    void freeResourceParam(UserResourceParam*);

    void* getAccessor() const;
    void* getAccessorPtr();
    u64 getSolvedAssetParameterELink(ResAssetCallTable const&);
    u64 getSystem() const;

    void onSetupResourceParam(UserResourceParam*, ParamDefineTable const*, sead::Heap*);

    void releaseOneEmitterInstance(UserResourceParamELink*, ParamDefineTable const*);
    void solveAssetParam(UserResourceELink*, ParamDefineTable const*, PtclResourceAccessorELink*);
    void solveResourceForChangeEset();

private:
};

class UserResourceSLink {
    virtual ~UserResourceSLink();

public:
    UserResourceSLink(User*, sead::Heap*);

    void allocResourceParam(sead::Heap);
    void freeResourceParam(UserResourceParam*);

    void* getAccessor() const;
    void* getAccessorPtr();
    u64 getSystem() const;
    u64 getUserParam() const;

    // bool isEnableAssetInfoReader(aal::IAssetInfoReadable**) const;

    void onSetupResourceParam(UserResourceParam*, ParamDefineTable const*, sead::Heap*);

    // void solveIsLoop(aal::IAssetInfoReadable*);
    // void solveIsLoop(UserResourceParam*, ParamDefineTable const*, aal::IAssetInfoReadable*)

private:
};
}  // namespace xlink2