#pragma once

#include "heap/seadHeap.h"

namespace xlink2 {
class GroupTable {
public:
    GroupTable(int, sead::Heap*);

    void batchEntry(int, ...);

    u32 getId(char const*) const;
    u64 getKeyLength(u32) const;

    void* searchKey(int) const;

private:
    s32 _0;
    s32 _1;
    void* _2;
};
static_assert(sizeof(GroupTable) == 0x10, "Wrong size for 'xlink2::GroupTable'");

}  // namespace xlink2