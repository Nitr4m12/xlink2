#include "xlink2/xlink2Util.h"

namespace xlink2 {
u64 sMinAddressLow = 0xFFFFFFFFFFFFFF;
u64 sMinAddressHigh = 0xFFFFFFFFFFFFFF;

// MATCHING
void setMinLargeAddressMask(u64 param_1) {
    if (param_1 < (sMinAddressHigh | sMinAddressLow)) {
        sMinAddressHigh = param_1 & 0xFFFFFFFF00000000;
        sMinAddressLow = param_1 & 0xFFFFFFFF;
    }
}
}  // namespace xlink2