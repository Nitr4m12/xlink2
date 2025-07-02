#pragma once

#include <heap/seadHeap.h>

namespace xlink2 {
class GroupTable {
public:
    struct Entry {
        const char* key;
        s32 id;
    };

    GroupTable(s32, sead::Heap*);

    void batchEntry(s32, ...);

    s32 getId(const char*) const;
    u64 getKeyLength(u32) const;

    const char* searchKey(s32) const;

private:
    s32 mCurrentIdx;
    s32 mNumEntries;
    Entry* mEntryBuffer;
};
static_assert(sizeof(GroupTable) == 0x10, "xlink2::GroupTable size mismatch");

}  // namespace xlink2