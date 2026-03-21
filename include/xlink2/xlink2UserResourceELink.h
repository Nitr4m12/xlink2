#pragma once

#include "xlink2/xlink2ResourceAccessorELink.h"
#include "xlink2/xlink2UserResource.h"

namespace xlink2 {
class PtclResourceAccessorELink;
class SystemELink;
class UserResourceParamELink;

class UserResourceELink : public UserResource {
public:
    UserResourceELink(User*, sead::Heap*);
    ~UserResourceELink() override;

    SolvedAssetParamELink* getSolvedAssetParameterELink(const ResAssetCallTable&);

    void solveResourceForChangeEset();
    void solveAssetParam(UserResourceELink*, const ParamDefineTable*, PtclResourceAccessorELink*);

    UserResourceParam* allocResourceParam_(sead::Heap*) override;
    void freeResourceParam_(UserResourceParam*) override;

    void releaseOneEmitterInstance(UserResourceParamELink*, const ParamDefineTable*);

    void onSetupResourceParam_(UserResourceParam*, const ParamDefineTable*, sead::Heap*) override;

    const ResourceAccessorELink& getAccessor() const override;
    ResourceAccessorELink* getAccessorPtr() override;
    System* getSystem() const override;

    const ResourceAccessorELink& getResourceAccessor() const { return mAccessor; }

private:
    bool _0;
    ResourceAccessorELink mAccessor;
};
static_assert(sizeof(UserResourceELink) == 0x50, "'xlink2::UserResourceELink' size mismatch");

}  // namespace xlink2