#pragma once

#include "heap/seadHeap.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserResourceParam.h"
namespace xlink2 {
class UserResourceSLink {
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
};
}