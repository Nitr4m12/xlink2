#pragma once

#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2ResActionTrigger.h"
#include "xlink2/xlink2ResPropertyTrigger.h"
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

    void setup(sead::Heap*);
    void setupRomResourceParam_(sead::Heap*);
    void setupEditorResourceParam(EditorResourceParam*, sead::Heap*);
    void setupResourceParam_(UserResourceParam*, ResUserHeader*, const CommonResourceParam*,
                             ParamDefineTable const*, sead::Heap*);

    const ResUserHeader* getUserHeader() const;
    bool searchAssetCallTableByName(Locator*, const char*) const;
    ResAssetCallTable* searchAssetCallTableByName(const char*) const;
    ResAssetCallTable* doBinarySearchAsset_(const char*, TriggerType) const;
    bool searchAssetCallTableByHash(Locator*, u32) const;

    ResAssetCallTable* getAssetCallTableItem(s32) const;
    ResActionTrigger* getActionTriggerTableItem(s32) const;
    ResPropertyTrigger* getPropertyTriggerTableItem(s32) const;
    ResAlwaysTrigger* getAlwaysTriggerTableItem(s32) const;

    virtual ResourceAccessor* getAccessor() const = 0;
    virtual ResourceAccessor* getAccessorPtr() = 0;
    virtual System* getSystem() const = 0;

    virtual UserResourceParam* allocResourceParam_(sead::Heap*) = 0;

    void destroy();
    virtual void freeResourceParam_(UserResourceParam*);

    u64 doBinarySearchToNameArray(s32*, const char*, u32*, u32);

    void solveNeedObserveFlag(UserResourceParam*);
    u64 solveNeedObserveFlagImpl(u32, ResAssetCallTable*, UserResourceParam*, ResUserHeader*);
    u64 searchAssetAllResource(const char*) const;
    bool hasGlobalPropertyTrigger() const;

    u64 getEditorSetupTime() const;
    void checkAndAddErrorMultipleKeyByTrigger(const ResAssetCallTable&, TriggerType);
    u64 searchAssetCallTableByGuid(Locator*, s32) const;

    virtual void onSetupResourceParam_(UserResourceParam*, const ParamDefineTable*, sead::Heap*);

    ResourceAccessor* getResourceAccessor() const { return mResourceAccessor; }
    UserResourceParam* getParam() const { return mParams[(s32)mResMode]; }
    sead::SafeArray<UserResourceParam*, 2> getParamBuffer() const { return mParams; }
    ResMode getResMode() const { return mResMode; }
    User* getUser() const { return mUser; }

    void setResMode(ResMode new_val) { mResMode = new_val; }

protected:
    struct Dummy {
        u8 bytes[0x18];
    };
    struct Dummy2 {
        u8 bytes[0x10];
    };
    struct Dummy3 {
        u8 bytes[0x20];
    };

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