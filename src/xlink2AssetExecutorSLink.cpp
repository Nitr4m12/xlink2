#include "xlink2/xlink2AssetExecutorSLink.h"

#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2UserResource.h"

namespace xlink2 {
AssetExecutorSLink::~AssetExecutorSLink() = default;

bool AssetExecutorSLink::isLoopEvent() const 
{
    if (!mpAssetCallTable)
        return false;

    auto* res_accessor = mpUserInstance->getUser()->getUserResource()->getAccessorPtr();
    return res_accessor->isLoopAsset(*mpAssetCallTable);
}

void AssetExecutorSLink::requestReEmit(bool check) 
{
    if (!check)
        _7 &= 0xfe;
    else
        _7 |= 1;
}

bool AssetExecutorSLink::isRequestReEmit() const 
{
    return _7 & 1;
}

void AssetExecutorSLink::onFinalize_() {
    _9 = nullptr;
}
}  // namespace xlink2