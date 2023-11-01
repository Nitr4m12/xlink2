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
    static RomResourceParam getEmptyRomResourceParam();
    static ResUserHeader getEmptyUserHeader();
    u64 load(void*, System*);

    void* searchResUserHeader(char const*) const;

    ParamDefineTable getParamDefineTable() const { return mParamDefineTable; }

private:
    RomResourceParam mRomResourceParam;
    ParamDefineTable mParamDefineTable;
};
static_assert(sizeof(ResourceBuffer) == 0xe8, "Wrong size for 'xlink2::ResourceBuffer'");

}  // namespace xlink2