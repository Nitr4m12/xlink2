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

    EnumPropertyDefinition(const char*, int, sead::Heap*, bool);
    EnumPropertyDefinition(const char*, int, bool, sead::Heap*, ...);
    EnumPropertyDefinition(const char*, int, char const**, bool, sead::Heap*);
    EnumPropertyDefinition(const char*, bool);
    void setEntries_(int, char const**);

    ~EnumPropertyDefinition() override;

    void entry(int, char const*);

    u64 getEntryKeyLength(u32) const;

    u32 searchEntryValueByKey(char const*) const;
    const char* searchEntryKeyByValue(int) const;

    void setEntryBuf_(s32, Entry*);

private:
    s32 mTotalEntryNum;
    s32 mEntryBufferSize;
    Entry* mEntryBuffer;
};
static_assert(sizeof(EnumPropertyDefinition) == 0x78, "Wrong size for 'xlink2::EnumPropertyDefinition'");

}  // namespace xlink2