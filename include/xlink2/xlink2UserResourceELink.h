#pragma once

#include "heap/seadHeap.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2SystemELink.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserResourceParam.h"
#include "xlink2/xlink2UserResourceParamELink.h"

namespace xlink2 {
class SystemELink;
class UserResourceELink : UserResource {
public:
    ~UserResourceELink() override;
    UserResourceELink(User*, sead::Heap*);

    UserResourceParam* allocResourceParam_(sead::Heap*) override;
    void freeResourceParam_(UserResourceParam*) override;

    ResourceAccessor* getAccessor() const;
    ResourceAccessor* getAccessorPtr() override;
    u64 getSolvedAssetParameterELink(ResAssetCallTable const&);
    SystemELink* getSystem() const;

    void onSetupResourceParam_(UserResourceParam*, ParamDefineTable const*, sead::Heap*) override;

    void releaseOneEmitterInstance(UserResourceParamELink*, ParamDefineTable const*);
    void solveAssetParam(UserResourceELink*, ParamDefineTable const*, PtclResourceAccessorELink*);
    void solveResourceForChangeEset();
};
}  // namespace xlink2