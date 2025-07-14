#include "xlink2/xlink2SystemELink.h"

namespace xlink2 {
u32 SystemELink::getResourceVersion() const {
    return 0x1e;
}

u32 SystemELink::getUserParamNum() const {
    return 0;
}

ILockProxy* SystemELink::getModuleLockObj() const {
    return sLockProxy;
}

}  // namespace xlink2