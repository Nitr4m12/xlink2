#include <xlink2/xlink2UserInstanceSLink.h>

#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2HoldMgr.h>
#include <xlink2/xlink2ILockProxy.h>
#include <xlink2/xlink2SystemSLink.h>
#include <xlink2/xlink2UserResourceSLink.h>

namespace xlink2 {
UserInstanceSLink::~UserInstanceSLink() = default;

void UserInstanceSLink::searchAndEmit(const char* asset_key_name, HandleSLink* handle)
{
    searchAndEmitImpl(asset_key_name, handle);
}

void UserInstanceSLink::emit(const Locator& locator, HandleSLink* handle)
{
    emitImpl(locator, handle);
}

void UserInstanceSLink::searchAndHold(const char* name, HandleSLink* handle)
{
    auto* system {mUser->getSystem()};
    system->getHoldMgr()->searchAndHold(name, handle, this);
}
}  // namespace xlink2