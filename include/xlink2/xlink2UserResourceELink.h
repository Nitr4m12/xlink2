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

    u64 getSolvedAssetParameterELink(const ResAssetCallTable&);

    void solveResourceForChangeEset();
    void solveAssetParam(UserResourceELink*, const ParamDefineTable*, PtclResourceAccessorELink*);

    UserResourceParam* allocResourceParam_(sead::Heap*) override;
    void freeResourceParam_(UserResourceParam*) override;

    void releaseOneEmitterInstance(UserResourceParamELink*, const ParamDefineTable*);

    void onSetupResourceParam_(UserResourceParam*, const ParamDefineTable*, sead::Heap*) override;

    ResourceAccessorELink* getAccessor() const override;
    ResourceAccessorELink* getAccessorPtr() override;
    System* getSystem() const override;

private:
    SystemELink* mSystem;
};
static_assert(sizeof(UserResourceELink) == 0x50, "Wrong size for xlink2::UserResourceELink");

}  // namespace xlink2