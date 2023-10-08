#pragma once

#include "heap/seadHeap.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2SystemSLink.h"
#include "xlink2/xlink2User.h"
#include "xlink2/xlink2UserResourceParam.h"

namespace aal {
class IAssetInfoReadable;
}

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

    bool isEnableAssetInfoReader(aal::IAssetInfoReadable**) const;

    void onSetupResourceParam_(UserResourceParam*, ParamDefineTable const*, sead::Heap*) override;

    void solveIsLoop(aal::IAssetInfoReadable*);
    void solveIsLoop(UserResourceParam*, ParamDefineTable const*, aal::IAssetInfoReadable*);

private:
};
static_assert(sizeof(UserResourceSLink) == 0x48, "Wrong size for 'xlink2::UserResourceSLink'");

}  // namespace xlink2