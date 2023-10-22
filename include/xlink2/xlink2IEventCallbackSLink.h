#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace aal {
class AssetInfo;
}

namespace xlink2 {
class UserInstanceSLink;
struct ResAssetCallTable;

class IEventCallbackSLink {
public:
    struct EventArg {};

    u32 eventActivating(const EventArg&);
    void eventActivated(const EventArg&);

    u32 soundPrePlay(const EventArg&);

    void eventCalced(const EventArg&);

    u32 replaceAssetInfo(aal::AssetInfo*, const sead::SafeString&, UserInstanceSLink const*,
                         ResAssetCallTable const*);

    void soundPlayed(const EventArg&);
};
}  // namespace xlink2