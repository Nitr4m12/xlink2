#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {
extern u64 sMinAddressLow;
extern u64 sMinAddressHigh;

void setMinLargeAddressMask(u64);

template <typename T, u64 MinAddress = 0x100000000>
T* calcOffset(const u32& offset) {
    return (T*)((offset >= sMinAddressLow) ? (offset | sMinAddressHigh) :
                                        (offset | sMinAddressHigh) + MinAddress);
}

}  // namespace xlink2