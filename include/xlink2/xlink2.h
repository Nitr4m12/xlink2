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

class PtclResourceAccessorELink {

};
class RandomContainer {
public:
    ~RandomContainer();
    void calc();
    bool start();

private:
};
class RandomContainer2 {
    ~RandomContainer2();
    void* start();
};

class S32PropertyDefinition;
}  // namespace xlink2
