#include "xlink2/xlink2IEventCallbackSLink.h"

namespace xlink2 {
u32 IEventCallbackSLink::eventActivating(const EventArg& /*unused*/) {
    return 0;
}
void IEventCallbackSLink::eventActivated(const EventArg& /*unused*/) {}

u32 IEventCallbackSLink::soundPrePlay(const EventArg& /*unused*/) {
    return 0;
}

void IEventCallbackSLink::eventCalced(const EventArg& /*unused*/) {}

u32 IEventCallbackSLink::replaceAssetInfo(aal::AssetInfo* /*unused*/,
                                          const sead::SafeString& /*unused*/,
                                          const UserInstanceSLink* /*unused*/,
                                          const ResAssetCallTable* /*unused*/) {
    return 0;
}

void IEventCallbackSLink::soundPlayed(const EventArg& /*unused*/) {}
}  // namespace xlink2