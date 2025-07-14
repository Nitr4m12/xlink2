#pragma once

#include "heap/seadHeap.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2ResourceAccessorSLink.h"
#include "xlink2/xlink2SystemSLink.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserResourceParam.h"

namespace aal {
class IAssetInfoReadable;
}

namespace xlink2 {
class UserResourceSLink : UserResource {
public:
    UserResourceSLink(User*, sead::Heap*);
    ~UserResourceSLink() override = default;

    u64 getUserParam() const;

    void solveIsLoop(aal::IAssetInfoReadable*);
    void solveIsLoop_(UserResourceParam*, const ParamDefineTable*, aal::IAssetInfoReadable*);

    bool isEnableAssetInfoReader_(aal::IAssetInfoReadable**) const;

    void allocResourceParam(sead::Heap);
    void freeResourceParam_(UserResourceParam*) override;
    void onSetupResourceParam_(UserResourceParam*, ParamDefineTable const*, sead::Heap*) override;

    ResourceAccessorSLink* getAccessor() const override;
    ResourceAccessorSLink* getAccessorPtr() override;
    System* getSystem() const override;

private:
};
static_assert(sizeof(UserResourceSLink) == 0x48, "xlink2::UserResourceSLink size mismatch");

}  // namespace xlink2