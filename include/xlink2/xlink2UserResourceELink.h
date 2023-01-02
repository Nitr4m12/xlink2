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
    virtual ~UserResourceELink();

public:
    UserResourceELink(User*, sead::Heap*);

    void allocResourceParam(sead::Heap);
    void freeResourceParam(UserResourceParam*);

    void* getAccessor() const;
    void* getAccessorPtr();
    u64 getSolvedAssetParameterELink(ResAssetCallTable const&);
    u64 getSystem() const;

    void onSetupResourceParam(UserResourceParam*, ParamDefineTable const*, sead::Heap*);

    void releaseOneEmitterInstance(UserResourceParamELink*, ParamDefineTable const*);
    void solveAssetParam(UserResourceELink*, ParamDefineTable const*, PtclResourceAccessorELink*);
    void solveResourceForChangeEset();

private:
    UserResourceParam* mUserResourceParam;
    void* _0;
    u8 _1;
    ResourceAccessor* mResourceAccessor;
    void* _2;
    UserResourceELink* mUserResourceELink;
    SystemELink* mSystem;
};
}