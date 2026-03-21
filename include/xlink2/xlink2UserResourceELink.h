#pragma once

#include "xlink2/xlink2ResourceAccessorELink.h"
#include "xlink2/xlink2SolvedAssetParam.h"
#include "xlink2/xlink2UserResource.h"
#include "xlink2/xlink2UserResourceParamELink.h"

namespace xlink2 {
class PtclResourceAccessorELink;
class SystemELink;

class UserResourceELink : public UserResource {
public:
    UserResourceELink(User*, sead::Heap*);
    ~UserResourceELink() override;

    SolvedAssetParamELink* getSolvedAssetParameterELink(const ResAssetCallTable&) const;

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
    bool _0x28;
    ResourceAccessorELink mAccessor;
};
static_assert(sizeof(UserResourceELink) == 0x50, "'xlink2::UserResourceELink' size mismatch");

}  // namespace xlink2