#pragma once

#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserResourceParam.h"

namespace xlink2 {
class System;
class ResourceAccessor;
class User;
struct UserResourceParam;

class UserResource {
public:
    virtual ~UserResource();
    explicit UserResource(User*);

    void setup(sead::Heap*);
    void setupRomResourceParam_(sead::Heap*);
    void setupEditorResourceParam_(EditorResourceParam*, sead::Heap*);
    void setupResourceParam_(UserResourceParam*, ResUserHeader*, CommonResourceParam const*,
                        ParamDefineTable const*, sead::Heap*);

    const ResUserHeader* getUserHeader() const;
    ResAssetCallTable* searchAssetCallTableByName(Locator*, char const*) const;
    ResAssetCallTable* searchAssetCallTableByName(char const*) const;
    u32* doBinarySearchAsset_(char const*, TriggerType) const;
    ResAssetCallTable* searchAssetCallTableByHash(Locator*, u32) const;

    ResAssetCallTable* getAssetCallTableItem(s32) const;
    void* getActionTriggerTableItem(s32) const;
    void* getPropertyTriggerTableItem(s32) const;
    ResAlwaysTrigger* getAlwaysTriggerTableItem(s32) const;

    virtual ResourceAccessor* getAccessor() const = 0;
    virtual ResourceAccessor* getAccessorPtr() = 0;
    virtual System* getSystem() const = 0;

    virtual UserResourceParam* allocResourceParam_(sead::Heap*) = 0;

    void destroy();

    u64 doBinarySearchToNameArray(s32*, char const*, u32*, u32);

    void solveNeedObserveFlag(UserResourceParam*);
    u64 solveNeedObserveFlagImpl(u32, ResAssetCallTable*, UserResourceParam*, ResUserHeader*);
    u64 searchAssetAllResource(char const*) const;
    bool hasGlobalPropertyTrigger() const;

    u64 getEditorSetupTime() const;
    void checkAndAddErrorMultipleKeyByTrigger(ResAssetCallTable const&, TriggerType);
    u64 searchAssetCallTableByGuid(Locator*, s32) const;

    virtual void freeResourceParam_(UserResourceParam*);
    virtual void onSetupResourceParam_(UserResourceParam*, ParamDefineTable const*, sead::Heap*);

    ResourceAccessor* getResourceAccessor() const { return mResourceAccessor; }
    sead::SafeArray<UserResourceParam*, 2> getParams() const { return mParams; }
    ResMode getResMode() const { return mResMode; }

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
};
}  // namespace xlink2