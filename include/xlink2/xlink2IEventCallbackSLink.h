#pragma once

#include <prim/seadSafeString.h>

#include "xlink2/xlink2EventSLink.h"
#include "xlink2/xlink2HandleSLink.h"
#include "xlink2/xlink2Resource.h"

namespace aal {
class AssetInfo;
}

namespace xlink2 {
class UserInstanceSLink;

class IEventCallbackSLink {
public:
    struct EventArg {
        UserInstanceSLink* pUserInstance {};
        HandleSLink* pHandle {};
        const ResAssetCallTable* pAssetCallTable {};
        AssetExecutorSLink* pAssetExecutor {};
        EventSLink* pEvent {};
    };

    virtual bool eventActivating(const EventArg&);
    virtual void eventActivated(const EventArg&);

    virtual u32 soundPrePlay(const EventArg&);

    virtual void eventCalced(const EventArg&);

    virtual u32 replaceAssetInfo(aal::AssetInfo*, const sead::SafeString&, const UserInstanceSLink*,
                                 const ResAssetCallTable*);

    virtual void soundPlayed(const EventArg&);
};
}  // namespace xlink2