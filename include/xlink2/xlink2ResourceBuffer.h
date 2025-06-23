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

    ResUserHeader* searchResUserHeader(char const*) const;

    ParamDefineTable getParamDefineTable() { return mParamDefineTable; }
    RomResourceParam getRomResourceParam() { return mRomResourceParam; }

private:
    RomResourceParam mRomResourceParam;
    ParamDefineTable mParamDefineTable;
};
static_assert(sizeof(ResourceBuffer) == 0xe8, "Wrong size for 'xlink2::ResourceBuffer'");

}  // namespace xlink2