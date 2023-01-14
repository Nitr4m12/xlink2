#include "xlink2/xlink2SystemSLink.h"

namespace xlink2 {
u64 SystemSLink::getResourceVersion() const {
    return 0x1c;
}

u64 SystemSLink::getUserParamNum() const {
    return 8;
}

bool SystemSLink::isEnableUserAssetInfoReadable() const {
    return false;
}

ILockProxy* SystemSLink::getModuleLockObj() const {
    return sLockProxy;
}
}  // namespace xlink2