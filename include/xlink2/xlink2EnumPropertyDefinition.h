#pragma once

#include <heap/seadHeap.h>

#include "xlink2/xlink2PropertyDefinition.h"

namespace xlink2 {
class EnumPropertyDefinition : PropertyDefinition {
public:
    class Entry {};

    EnumPropertyDefinition(char const*, int, sead::Heap*);
    EnumPropertyDefinition(char const*, int, bool, sead::Heap*, ...);
    EnumPropertyDefinition(char const*, int, char const**, bool, sead::Heap*);
    EnumPropertyDefinition(char const*, bool);

    ~EnumPropertyDefinition() override;

    void entry(int, char const*);

    u64 getEntryKeyLength(u32) const;

    void* searchEntryKeyByValue(int) const;
    void* searchEntryValueByKey(char const*) const;

    void setEntries(int, char const**);
    void setEntryBuf(s32, Entry*);

private:
    u32 _10;
    s32 _11;
    Entry* mEntry;

    // size=0x78
};
}  // namespace xlink2