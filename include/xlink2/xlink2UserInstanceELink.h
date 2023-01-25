#pragma once

#include "xlink2/xlink2HandleELink.h"
#include "xlink2/xlink2IEventCallbackELink.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2ResourceAccessorELink.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserResourceELink.h"

namespace xlink2 {
class UserResourceELink;

class UserInstanceELink : UserInstance {
    ~UserInstanceELink() override;

public:
    UserInstanceELink(UserInstance::CreateArg const&, System*, User*, sead::Heap*);

    void allocInstanceParam(sead::Heap*);
    void emit(Locator const&);
    void emit(Locator const&, HandleELink*);
    void fadeIfLoopEffect();
    void freeInstanceParam_(UserInstanceParam*, ResMode);

    UserInstanceELink getDefaultGroup() const;
    ResourceAccessor* getResourceAccessor() const;
    UserResource* getResourceELink() const;

    void initModelAssetConnection(ResMode, ParamDefineTable const*, sead::Heap*);

    void makeDebugStringEvent(sead::BufferedSafeString*, sead::SafeString const&) const;

    void onDestroy_();
    void onPostCalc();
    void onReset();
    void onSetupInstanceParam(ResMode, sead::Heap*);

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