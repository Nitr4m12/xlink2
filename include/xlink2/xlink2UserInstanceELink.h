#pragma once

#include "xlink2/xlink2HandleELink.h"
#include "xlink2/xlink2IEventCallbackELink.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserResourceELink.h"

namespace xlink2 {
class UserResourceELink;

class UserInstanceELink : public UserInstance {

public:
    UserInstanceELink(UserInstance::CreateArg const&, System*, User*, sead::Heap*);

    void searchAndEmit(char const*);
    void searchAndEmit(char const*, HandleELink*);

    void emit(Locator const&);
    void emit(Locator const&, HandleELink*);

    void searchAndHold(char const*);
    void searchAndHold(char const*, HandleELink*);

    void fadeIfLoopEffect();

    ResourceAccessorELink* getResourceAccessor() const;
    UserResource* getResourceELink() const;

    void onPostCalc_() override;
    void onReset_() override;
    void onDestroy_() override;

    UserInstanceParam* allocInstanceParam_(sead::Heap*) override;
    void freeInstanceParam_(UserInstanceParam*, ResMode) override;

    void onSetupInstanceParam_(ResMode, sead::Heap*) override;

    void initModelAssetConnection_(ResMode, ParamDefineTable const*, sead::Heap*) override;

    void makeDebugStringEvent(sead::BufferedSafeString*, sead::SafeString const&) const override;

    ~UserInstanceELink() override;

    u32 getDefaultGroup() const override;
private:
    IEventCallbackELink* mEventCallback;
    u16 _6;
    u8 mDefaultGroup;
    PtclResourceAccessorELink* mPtclResourceAccessor;
};
static_assert(sizeof(UserInstanceELink) == 0x108, "Wrong size for 'xlink2::UserInstance'");

}  // namespace xlink2