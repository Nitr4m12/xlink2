#pragma once

#include <heap/seadHeap.h>

#include "xlink2/xlink2PropertyDefinition.h"

namespace xlink2 {
class EnumPropertyDefinition : PropertyDefinition {
    virtual ~EnumPropertyDefinition();

public:
    class Entry {};

    EnumPropertyDefinition(char const*, int, sead::Heap*);
    EnumPropertyDefinition(char const*, int, bool, sead::Heap*, ...);
    EnumPropertyDefinition(char const*, int, char const**, bool, sead::Heap*);
    EnumPropertyDefinition(char const*, bool);

    void entry(int, char const*);

    u64 getEntryKeyLength(u32) const;

    void* searchEntryKeyByValue(int) const;
    void* searchEntryValueByKey(char const*) const;

    void setEntries(int, char const**);
    void setEntryBuf(s32, Entry*);

private:
    void* _0;
    void* _1;
    u32 _2;

    // 0x64
    u8 _9;
    u32 _10;
    s32 _11;
    Entry* mEntry;
};
}  // namespace xlink2