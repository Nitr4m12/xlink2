#include "xlink2/xlink2SystemSLink.h"
#include "xlink2/xlink2ILockProxy.h"

namespace xlink2 {
SystemSLink::SystemSLink() = default;

SystemSLink::~SystemSLink()
{
    if (mpEventPool != nullptr) {
        delete[] (mpEventPool);
        mpEventPool = nullptr;
    }
    if (mIsAllocatedLock) {
        delete sLockProxy;
        sLockProxy = nullptr;
    }
}

u32 SystemSLink::getResourceVersion() const {
    return 0x1c;
}

u32 SystemSLink::getUserParamNum() const {
    return 8;
}

bool SystemSLink::isEnableUserAssetInfoReadable() const {
    return false;
}

ILockProxy* SystemSLink::getModuleLockObj() const {
    return sLockProxy;
}
}  // namespace xlink2