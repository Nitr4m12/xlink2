#pragma once

#include "xlink2/xlink2RomResourceParam.h"
#include "xlink2/xlink2System.h"

namespace xlink2 {
class ResourceBuffer {
public:
    ResourceBuffer();
    virtual ~ResourceBuffer();

    bool load(void* bin, System* system);
    
    ResUserHeader* searchResUserHeader(const char* user_name) const;
    void applyGlobalPropertyDefinition(System* system);
    
    static RomResourceParam getEmptyRomResourceParam();
    static ResUserHeader getEmptyUserHeader();
    
    const ParamDefineTable* getParamDefineTable() { return &mParamDefineTable; }
    RomResourceParam getRomResourceParam() { return mRomResourceParam; }

private:
    RomResourceParam mRomResourceParam;
    ParamDefineTable mParamDefineTable;
};
static_assert(sizeof(ResourceBuffer) == 0xe8, "Wrong size for 'xlink2::ResourceBuffer'");

}  // namespace xlink2