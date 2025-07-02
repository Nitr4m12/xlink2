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
            mEntryBuffer[i].value = i;
            mEntryBuffer[i].key = va_arg(args, const char*);
        }
    }
    va_end(args);
    mCurrentIdx = num_entries;
}

} // namespace xlink2