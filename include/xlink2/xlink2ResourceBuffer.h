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

    ParamDefineTable* getParamDefineTable() const { return mParamDefineTable; }

private:
    // size = 0xe8
    RomResourceParam* mRomResourceParam;
    void* _0;
    void* _1;
    void* _2;
    u32 _3;
    void* _4;
    u32 _5;
    void* _6;
    void* _7;
    void* _8;
    void* _9;
    void* _10;
    void* _11;
    void* _12;
    u32 _13;
    void* _14;
    void* _15;
    u32 _16;
    u8 _17;
    u8 _18[3];
    s32 _19;
    u8 _20;
    ParamDefineTable* mParamDefineTable;

    // 0xe0
    // u8
};
}  // namespace xlink2