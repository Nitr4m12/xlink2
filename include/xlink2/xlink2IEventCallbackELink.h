#pragma once

#include <gfx/seadTextWriter.h>
#include <prim/seadSafeString.h>

#include "xlink2/xlink2AssetExecutorELink.h"
#include "xlink2/xlink2Resource.h"
#include "xlink2/xlink2UserInstanceELink.h"
#include "xlink2/xlink2EventELink.h"

namespace sead::ptcl {
class EmitterSet;
}  // namespace sead::ptcl

namespace xlink2 {
class ResourceAccessorELink;

class IEventCallbackELink {
public:
    struct EventArg {
        EventArg(const ResAssetCallTable* asset_ctb, UserInstanceELink* user_instance, 
                 HandleELink* handle, AssetExecutorELink* asset_executor, EventELink* event)
            :  pAssetCallTable(asset_ctb), 
               pUserInstance(user_instance), 
               pHandle(handle),
               pAssetExecutor(asset_executor), 
               pEvent(event) {}
    
        [[maybe_unused]] void* _0x0;
        [[maybe_unused]] void* _0x8;
        const ResAssetCallTable* pAssetCallTable;
        UserInstanceELink* pUserInstance;
        HandleELink* pHandle;
        AssetExecutorELink* pAssetExecutor;
        EventELink* pEvent;
    };

    virtual void eventCreate(const EventArg&);
    virtual void eventDestroy(const EventArg&);
    virtual void eventActivated(const EventArg&);

    virtual u32 effectPreEmit(const EventArg&);
    
    virtual void effectEmited(const EventArg&);
    virtual void eventDeleted(const EventArg&);
    virtual void colorApplied(const EventArg&);
    virtual void eventCalced(const EventArg&);

    virtual void replaceResEset(ResEset*, const ResAssetCallTable&, const ResourceAccessorELink&,
                                const char *);

    virtual void drawDebugInformation(sead::TextWriter*);
    virtual void drawEsetDebugInformation(sead::BufferedSafeString*, sead::ptcl::EmitterSet*);

};
}  // namespace xlink2