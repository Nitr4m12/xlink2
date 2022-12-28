#pragma once

#include "xlink2/xlink2HandleELink.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2User.h"

namespace xlink2 {
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
}