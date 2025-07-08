#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {
extern u64 sMinAddressLow;
extern u64 sMinAddressHigh;

static void setMinLargeAddressMask(u64 mask) {
    if (mask < (sMinAddressHigh | sMinAddressLow)) {
        sMinAddressHigh = mask & 0xFFFFFFFF00000000;
        sMinAddressLow = mask & 0xFFFFFFFF;
    }
}

template <typename T>
T* calcOffset(const u32& offset) {
    return reinterpret_cast<T*>((offset >= sMinAddressLow) ? (offset | sMinAddressHigh) :
                                        (offset | sMinAddressHigh) + 0x100000000);
}

}  // namespace xlink2