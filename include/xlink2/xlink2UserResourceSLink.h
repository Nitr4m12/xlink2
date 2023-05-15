#pragma once

#include "heap/seadHeap.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2SystemSLink.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserResourceParam.h"

namespace xlink2 {
class SystemSLink;
class UserResourceSLink : UserResource {
    ~UserResourceSLink() override;

public:
    UserResourceSLink(User*, sead::Heap*);

    void allocResourceParam(sead::Heap);
    void freeResourceParam_(UserResourceParam*) override;

    ResourceAccessor* getAccessor() const override;
    ResourceAccessor* getAccessorPtr() override;
    System* getSystem() const override;
    u64 getUserParam() const;

    // bool isEnableAssetInfoReader(aal::IAssetInfoReadable**) const;

    void onSetupResourceParam_(UserResourceParam*, ParamDefineTable const*, sead::Heap*) override;

    // void solveIsLoop(aal::IAssetInfoReadable*);
    // void solveIsLoop(UserResourceParam*, ParamDefineTable const*, aal::IAssetInfoReadable*)

private:
    UserResourceParam* mUserResourceParam;
    void* _0;
    u8 _1;
    ResourceAccessorSLink* mResourceAccessor;
    void* _2;
    UserResourceSLink* mUserResource;
    SystemSLink* mSystem;
};
}  // namespace xlink2