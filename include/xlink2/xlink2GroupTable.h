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
};
}  // namespace xlink2