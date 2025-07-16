#pragma once

#include <prim/seadSafeString.h>

#include "xlink2/xlink2Resource.h"

namespace aal {
class AssetInfo;
}

namespace xlink2 {
class UserInstanceSLink;

class IEventCallbackSLink {
public:
    struct EventArg {};

    u32 eventActivating(const EventArg&);
    void eventActivated(const EventArg&);

    u32 soundPrePlay(const EventArg&);

    void eventCalced(const EventArg&);

    u32 replaceAssetInfo(aal::AssetInfo*, const sead::SafeString&, const UserInstanceSLink*,
                         const ResAssetCallTable*);

    void soundPlayed(const EventArg&);
};
}  // namespace xlink2