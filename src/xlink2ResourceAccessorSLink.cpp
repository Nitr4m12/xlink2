#include <xlink2/xlink2ResourceAccessorSLink.h>

namespace xlink2 {
bool ResourceAccessorSLink::isBoneNameOverwritten(u32 p1) const {
    return isParamOverwritten(p1, 0xf);
}
}