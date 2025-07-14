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
    UserInstanceELink(const UserInstance::CreateArg&, System*, User*, sead::Heap*);
    ~UserInstanceELink() override;

    void searchAndEmit(const char*);
    void searchAndEmit(const char*, HandleELink*);

    void emit(const Locator&);
    void emit(const Locator&, HandleELink*);

    void searchAndHold(const char*);
    void searchAndHold(const char*, HandleELink*);

    void fadeIfLoopEffect();

    ResourceAccessorELink* getResourceAccessor() const;
    UserResourceELink* getResourceELink() const;

    void onPostCalc_() override;
    void onReset_() override;
    void onDestroy_() override;

    UserInstanceParam* allocInstanceParam_(sead::Heap*) override;
    void freeInstanceParam_(UserInstanceParam*, ResMode) override;

    void onSetupInstanceParam_(ResMode, sead::Heap*) override;

    void initModelAssetConnection_(ResMode, ParamDefineTable const*, sead::Heap*) override;

    void makeDebugStringEvent(sead::BufferedSafeString*, sead::SafeString const&) const override;

    u32 getDefaultGroup() const override;

private:
    void* _0xd8;
    void* _0xe0;
    void* _0xe8;
    IEventCallbackELink* mEventCallback;
    u16 _6;
    u8 mDefaultGroup;
    PtclResourceAccessorELink* mPtclResourceAccessor;
};
static_assert(sizeof(UserInstanceELink) == 0x108, "xlink2::UserInstanceELink size mismatch");

}  // namespace xlink2