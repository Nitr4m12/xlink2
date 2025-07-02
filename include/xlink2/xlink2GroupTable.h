#pragma once

#include "heap/seadHeap.h"

namespace xlink2 {
class GroupTable {
public:
    struct Entry {
        const char* key;
        s32 value;
    };

    GroupTable(int, sead::Heap*);

    void batchEntry(int, ...);

    u32 getId(char const*) const;
    u64 getKeyLength(u32) const;

    void* searchKey(int) const;

private:
    s32 mCurrentIdx;
    s32 mNumEntries;
    Entry* mEntryBuffer;
};
static_assert(sizeof(GroupTable) == 0x10, "xlink2::GroupTable size mismatch");

}  // namespace xlink2