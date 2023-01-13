#include "xlink2/xlink2AssetExecutorSLink.h"

namespace xlink2 {
u8 AssetExecutorSLink::isRequestReEmit() const {
    return _7 & 1;
}

void AssetExecutorSLink::onFinalize_() {
    _9 = nullptr;
}

void AssetExecutorSLink::requestReEmit(bool check) {
    if (!check)
        _7 &= 0xfe;
    else
        _7 |= 1;
}
}  // namespace xlink2