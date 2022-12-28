#pragma once

#include <heap/seadHeap.h>
#include "xlink2/xlink2.h"

namespace xlink2 {
class ResourceBuffer {
    virtual ~ResourceBuffer();
public:
    ResourceBuffer();

    void applyGlobalPropertyDefinition(System*);
    void getEmptyRomResourceParam();
    void getEmptyUserHeader();
    u64 load(void*, System*);

    u64 searchResUserHeader(char const*) const;
private:
};
}