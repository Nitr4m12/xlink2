#pragma once

#include "xlink2/xlink2ResourceAccessorSLink.h"
#include "xlink2/xlink2SystemSLink.h"
#include "xlink2/xlink2UserResource.h"
#include "xlink2/xlink2UserResourceParamSLink.h"

namespace aal {
class IAssetInfoReadable;
}

namespace xlink2 {
class UserResourceSLink : public UserResource {
public:
    UserResourceSLink(User*, [[maybe_unused]] sead::Heap*);
    ~UserResourceSLink() override;

    const ResParam* getUserParam() const;

    void solveIsLoop(aal::IAssetInfoReadable*);
    void solveIsLoop_(UserResourceParam*, const ParamDefineTable*, aal::IAssetInfoReadable*);

    bool isEnableAssetInfoReader_(aal::IAssetInfoReadable**) const;

    UserResourceParamSLink* allocResourceParam_(sead::Heap*) override;
    void freeResourceParam_(UserResourceParam*) override;
    void onSetupResourceParam_(UserResourceParam*, const ParamDefineTable*, sead::Heap*) override;

    const ResourceAccessorSLink& getAccessor() const override;
    ResourceAccessorSLink* getAccessorPtr() override;
    SystemSLink* getSystem() const override;

    const ResourceAccessorSLink& getResourceAccessor() const { return mAccessor; }

private:
    ResourceAccessorSLink mAccessor;
};
static_assert(sizeof(UserResourceSLink) == 0x48, "xlink2::UserResourceSLink size mismatch");

}  // namespace xlink2