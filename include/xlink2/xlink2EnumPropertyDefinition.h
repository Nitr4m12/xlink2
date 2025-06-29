#pragma once

#include <heap/seadHeap.h>

#include "xlink2/xlink2PropertyDefinition.h"

namespace xlink2 {
class EnumPropertyDefinition : PropertyDefinition {
public:
    struct Entry {
        const char* key; 
        s32 value;
    };

    EnumPropertyDefinition(const char*, s32, sead::Heap*, bool);
    EnumPropertyDefinition(const char*, s32, bool, sead::Heap*, ...);
    EnumPropertyDefinition(const char*, s32, char const**, bool, sead::Heap*);
    EnumPropertyDefinition(const char*, bool);
    void setEntries_(s32, char const**);

    ~EnumPropertyDefinition() override;

    void entry(s32, const char*);

    s32 getEntryKeyLength(u32) const;

    s32 searchEntryValueByKey(const char*) const;
    const char* searchEntryKeyByValue(s32) const;

    void setEntryBuf_(s32, Entry*);

private:
    s32 mTotalEntryNum;
    s32 mEntryBufferSize;
    Entry* mEntryBuffer;
};
static_assert(sizeof(EnumPropertyDefinition) == 0x78, "Wrong size for 'xlink2::EnumPropertyDefinition'");

}  // namespace xlink2