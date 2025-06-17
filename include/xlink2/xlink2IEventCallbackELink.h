#pragma once

#include <prim/seadSafeString.h>

#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResEset.h"
#include "xlink2/xlink2ResourceAccessorELink.h"

namespace sead::ptcl {
class EmitterSet;
}  // namespace sead::ptcl

namespace xlink2 {
class IEventCallbackELink {
public:
    struct EventArg {};

    virtual void eventCreate(const EventArg&);
    virtual void eventDestroy(const EventArg&);
    virtual void eventActivated(const EventArg&);

    virtual u32 effectPreEmit(const EventArg&);

    virtual void replaceResEset(ResEset*, const ResAssetCallTable&, const ResourceAccessorELink&,
                             char const*);

    virtual void drawDebugInformation(sead::TextWriter*);
    virtual void drawEsetDebugInformation(sead::BufferedSafeString*, sead::ptcl::EmitterSet*);

    virtual void effectEmited(const EventArg&);
    virtual void eventDeleted(const EventArg&);
    virtual void colorApplied(const EventArg&);
    virtual void eventCalced(const EventArg&);
};
}  // namespace xlink2