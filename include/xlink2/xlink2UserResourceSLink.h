#pragma once

#include "heap/seadHeap.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2SystemSLink.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserResourceParam.h"
namespace xlink2 {
class SystemSLink;
class UserResourceSLink : UserResource {
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
    UserResourceParam* mUserResourceParam;
    void* _0;
    u8 _1;
    ResourceAccessor* mResourceAccessor;
    void* _2;
    UserResourceSLink* mUserResourceELink;
    SystemSLink* mSystem;
};
}