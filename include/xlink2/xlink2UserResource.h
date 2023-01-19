#pragma once

#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2PtclResourceAccessorELink.h"
#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2ResourceParamCreator.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserResourceParam.h"

namespace xlink2 {
class System;
class ResourceAccessor;
class User;

class UserResource {
public:
    explicit UserResource(User*);
    virtual ~UserResource();

    void checkAndAddErrorMultipleKeyByTrigger(ResAssetCallTable const&, TriggerType);
    void destroy();

    u32* doBinarySearchAsset_(char const*, TriggerType) const;
    u64 doBinarySearchToNameArray(s32*, char const*, u32*, u32);

    virtual void func1();
    virtual void func2();
    virtual void func3();
    virtual void func4();
    virtual void freeResourceParam_(UserResourceParam*);

    void* getActionTriggerTableItem(s32) const;
    void* getAlwaysTriggerTableItem(s32) const;
    void* getAssetCallTableItem(s32) const;
    u64 getEditorSetupTime() const;
    u64 getPropertyTriggerTableItem(s32) const;
    ResUserHeader* getUserHeader() const;

    ResourceAccessor* getResourceAccessor() const { return mResourceAccessor; }

    u64 hasGlobalPropertyTrigger() const;

    virtual void onSetupResourceParam_(UserResourceParam*, ParamDefineTable const*, sead::Heap*);

    u64 searchAssetAllResource(char const*) const;
    u64 searchAssetCallTableByGuid(Locator*, s32) const;
    u64 searchAssetCallTableByHash(Locator*, u32) const;
    u64 searchAssetCallTableByName(Locator*, char const*) const;
    u64 searchAssetCallTableByName(char const*) const;

    void setup(sead::Heap*);
    void setupEditorResourceParam(EditorResourceParam*, sead::Heap*);
    void setupResourceParam(UserResourceParam*, ResUserHeader*, CommonResourceParam const*,
                            ParamDefineTable const*, sead::Heap*);
    void setupRomResourceParam(sead::Heap*);

    void solveNeedObserveFlag(UserResourceParam*);
    u64 solveNeedObserveFlagImpl(u32, ResAssetCallTable*, UserResourceParam*, ResUserHeader*);

    System* getSystem();

protected:
    struct Dummy { u8 bytes[0x18]; };
    struct Dummy2 { u8 bytes[0x10]; };
    struct Dummy3 { u8 bytes[0x20]; };

    User* mUser;
    ResMode mResMode;
    u32 _5;
    sead::SafeArray<UserResourceParam*, 2> mParams;
    u8 _2;
    ResourceAccessor* mResourceAccessor;
    void* _3;
    void* _4;
    System* mSystem;


};
}  // namespace xlink2