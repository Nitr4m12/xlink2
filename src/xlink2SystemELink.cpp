#include "xlink2/xlink2SystemELink.h"

namespace xlink2 {
u32 SystemELink::getResourceVersion() const {
    return 0x1e;
}

sead::SafeString* SystemELink::getModuleName() const
{
    return &sModuleName;
}

const sead::SafeString* SystemELink::getORIconString()
{
    return &sORIconString;
}

Event* SystemELink::getEventFromPool_(u32 idx) const
{
    if (idx < mMaxNumEventPool)
        return &mpEventPool[idx];

    return nullptr;
}

u32 SystemELink::getUserParamNum() const {
    return 0;
}

ILockProxy* SystemELink::getModuleLockObj() const {
    return sLockProxy;
}

}  // namespace xlink2