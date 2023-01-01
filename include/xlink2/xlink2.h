#pragma once

#include <thread/seadMutex.h>
#include <thread/seadSpinLock.h>

namespace xlink2 {

struct Handle {
    void* _0 = nullptr;
    int _8 = 0;
};

class F32PropertyDefinition;
template <typename T>
class FixedEnumPropertyDefinition;

namespace IEventCallbackELink {};
namespace IEventCallbackSLink {};

class S32PropertyDefinition;
}  // namespace xlink2
