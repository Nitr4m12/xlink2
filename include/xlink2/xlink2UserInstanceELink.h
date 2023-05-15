#pragma once

#include "xlink2/xlink2HandleELink.h"
#include "xlink2/xlink2IEventCallbackELink.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserResourceELink.h"

namespace xlink2 {
class UserResourceELink;

class UserInstanceELink : UserInstance {
    ~UserInstanceELink() override;

public:
    UserInstanceELink(UserInstance::CreateArg const&, System*, User*, sead::Heap*);

    void allocInstanceParam_(sead::Heap*) override;
    void emit(Locator const&);
    void emit(Locator const&, HandleELink*);
    void fadeIfLoopEffect();
    void freeInstanceParam_(UserInstanceParam*, ResMode) override;

    u32 getDefaultGroup() const override;
    ResourceAccessor* getResourceAccessor() const;
    UserResource* getResourceELink() const;

    void initModelAssetConnection_(ResMode, ParamDefineTable const*, sead::Heap*) override;

    void makeDebugStringEvent(sead::BufferedSafeString*, sead::SafeString const&) const override;

    void onDestroy_() override;
    void onPostCalc_() override;
    void onReset_() override;
    void onSetupInstanceParam_(ResMode, sead::Heap*) override;

    void searchAndEmit(char const*);
    void searchAndEmit(char const*, HandleELink*);
    void searchAndHold(char const*);
    void searchAndHold(char const*, HandleELink*);

private:
    IEventCallbackELink* mEventCallback;
    u16 _6;
    u8 mDefaultGroup;
    PtclResourceAccessorELink* mPtclResourceAccessor;
};
}  // namespace xlink2