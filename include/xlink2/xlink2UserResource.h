#pragma once

#include <container/seadSafeArray.h>
#include <time/seadDateTime.h>

#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2UserResourceParam.h"
#include "xlink2/xlink2User.h"

namespace xlink2 {
class ParamDefineTable;
class ResourceAccessor;
class System;

class UserResource {
public:
    explicit UserResource(User*);
    virtual ~UserResource() = default;

    void setup(sead::Heap*);
    void setupRomResourceParam_(sead::Heap*);
    void setupEditorResourceParam(EditorResourceParam*, sead::Heap*);
    void setupResourceParam_(UserResourceParam*, ResUserHeader*, const CommonResourceParam*,
                             const ParamDefineTable*, sead::Heap*);

    const ResUserHeader* getUserHeader() const;
    
    bool searchAssetCallTableByName(Locator*, const char*) const;
    ResAssetCallTable* searchAssetCallTableByName(const char*) const;
    ResAssetCallTable* doBinarySearchAsset_(const char*, [[maybe_unused]] TriggerType) const;
    bool searchAssetCallTableByHash(Locator*, u32) const;

    ResAssetCallTable* getAssetCallTableItem(s32) const;
    ResActionTrigger* getActionTriggerTableItem(s32) const;
    ResPropertyTrigger* getPropertyTriggerTableItem(s32) const;
    ResAlwaysTrigger* getAlwaysTriggerTableItem(s32) const;

    virtual const ResourceAccessor& getAccessor() const = 0;
    virtual ResourceAccessor* getAccessorPtr() = 0;
    virtual System* getSystem() const = 0;

    virtual UserResourceParam* allocResourceParam_(sead::Heap*) = 0;

    void destroy();
    virtual void freeResourceParam_(UserResourceParam*);

    static bool doBinarySearchToNameArray_(s32*, const char*, u32*, u32);

    static void solveNeedObserveFlag_(UserResourceParam*);
    static bool solveNeedObserveFlagImpl_(u32, ResAssetCallTable*, UserResourceParam*, ResUserHeader*);
    
    ResAssetCallTable* searchAssetAllResource(const char*) const;
    
    bool hasGlobalPropertyTrigger() const;

    sead::DateTime* getEditorSetupTime() const;
    void checkAndAddErrorMultipleKeyByTrigger(const ResAssetCallTable&, TriggerType);
    
    bool searchAssetCallTableByGuid(Locator*, s32) const;

    virtual void onSetupResourceParam_(UserResourceParam*, const ParamDefineTable*, sead::Heap*);

    UserResourceParam* getParam() const { return mParams[static_cast<s32>(mResMode)]; }
    UserResourceParam* getParam(ResMode mode) const { return mParams[static_cast<s32>(mode)]; }
    UserResourceParam* getParamWithSetupCheck() const { return getParam() != nullptr && getParam()->isSetup ? getParam() : nullptr; }
    
    sead::SafeArray<UserResourceParam*, 2> getParamBuffer() const { return mParams; }
    
    ResMode getResMode() const { return mResMode; }
    User* getUser() const { return mUser; }

    void setResMode(ResMode new_val) { mResMode = new_val; }

protected:
    User* mUser {};
    ResMode mResMode {ResMode::Rom};
    sead::SafeArray<UserResourceParam*, 2> mParams {};
};
}  // namespace xlink2