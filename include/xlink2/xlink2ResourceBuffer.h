#pragma once

#include <heap/seadHeap.h>
#include "xlink2/xlink2RomResourceParam.h"
#include "xlink2/xlink2System.h"

namespace xlink2 {
class ResourceBuffer {
public:
    ResourceBuffer();
    virtual ~ResourceBuffer();

    void applyGlobalPropertyDefinition(System*);
    void getEmptyRomResourceParam();
    void getEmptyUserHeader();
    u64 load(void*, System*);

    void* searchResUserHeader(char const*) const;

    ParamDefineTable getParamDefineTable() const { return mParamDefineTable; }

private:
    RomResourceParam mRomResourceParam;
    ParamDefineTable mParamDefineTable;
};
}  // namespace xlink2