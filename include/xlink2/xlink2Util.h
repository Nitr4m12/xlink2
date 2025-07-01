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

template <typename T, u64 MinAddress = 0x100000000>
T* calcOffset(const u32& offset) {
    return reinterpret_cast<T*>((offset >= sMinAddressLow) ? (offset | sMinAddressHigh) :
                                        (offset | sMinAddressHigh) + MinAddress);
}

}  // namespace xlink2