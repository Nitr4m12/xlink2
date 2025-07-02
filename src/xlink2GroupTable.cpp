#include "xlink2/xlink2GroupTable.h"

namespace xlink2 {
GroupTable::GroupTable(s32 num_entries, sead::Heap* heap)
    : mCurrentIdx(0), mNumEntries(num_entries)
{
    mEntryBuffer = new (heap) Entry[num_entries];
}

void GroupTable::batchEntry(s32 num_entries, ...)
{
    va_list args;
    va_start(args, num_entries);
    if (num_entries > 0) {
        for (u32 i{0}; i != num_entries; ++i) {
            mEntryBuffer[i].id = i;
            mEntryBuffer[i].key = va_arg(args, const char*);
        }
    }
    va_end(args);
    mCurrentIdx = num_entries;
}

s32 GroupTable::getId(const char* key) const
{
    for (s64 i {0}; i < mCurrentIdx; ++i) {
        if (strcmp(mEntryBuffer[i].key, key) == 0)
            return mEntryBuffer[i].id;
    }
    return -1;
}

s32 GroupTable::getKeyLength(u32 idx) const
{
    const char* key {mEntryBuffer[idx].key};
    for (s32 i {0}; i < 64; ++i) {
        if (key[i] == 0)
            return i;
    }

    return -1;
}

} // namespace xlink2