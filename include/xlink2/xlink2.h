#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {

struct Handle {
    void* _0 = nullptr;
    int _8 = 0;
};

class F32PropertyDefinition;
class S32PropertyDefinition;
template <typename T>
class FixedEnumPropertyDefinition;

namespace IEventCallbackELink {};
namespace IEventCallbackSLink {};

static u64 sMinAddressLow{0xFFFFFFFFFFFFFFFF};
static u64 sMinAddressHigh{0xFFFFFFFFFFFFFFFF};
}  // namespace xlink2
