#include "xlink2/xlink2IEventCallbackSLink.h"

namespace xlink2 {
bool IEventCallbackSLink::eventActivating([[maybe_unused]] const EventArg& arg)
{
    return false;
}
void IEventCallbackSLink::eventActivated([[maybe_unused]] const EventArg& arg) {}

u32 IEventCallbackSLink::soundPrePlay([[maybe_unused]] const EventArg& arg)
{
    return 0;
}

void IEventCallbackSLink::eventCalced([[maybe_unused]] const EventArg& arg) {}

u32 IEventCallbackSLink::replaceAssetInfo([[maybe_unused]] aal::AssetInfo* asset_info,
                                          [[maybe_unused]] const sead::SafeString& asset_name,
                                          [[maybe_unused]] const UserInstanceSLink* user_instance,
                                          [[maybe_unused]] const ResAssetCallTable* asset_ctb)
{
    return 0;
}

void IEventCallbackSLink::soundPlayed([[maybe_unused]] const EventArg& arg) {}
}  // namespace xlink2