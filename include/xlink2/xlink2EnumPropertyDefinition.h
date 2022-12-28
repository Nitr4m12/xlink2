#pragma once

#include "heap/seadHeap.h"

namespace xlink2 {
class EnumPropertyDefinition {
    virtual ~EnumPropertyDefinition();

public:
    EnumPropertyDefinition(char const*, int, sead::Heap*);
    EnumPropertyDefinition(char const*, int, bool, sead::Heap*, ...);
    EnumPropertyDefinition(char const*, int, char const**, bool, sead::Heap*);
    EnumPropertyDefinition(char const*, bool);

    void entry(int, char const*);

    u64 getEntryKeyLength(u32) const;

    void* searchEntryKeyByValue(int) const;
    void* searchEntryValueByKey(char const*) const;

    class Entry {};

    void setEntries(int, char const**);
    void setEntryBuf(s32, Entry*);

private:
};
}  // namespace xlink2