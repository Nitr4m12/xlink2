#include "xlink2/xlink2GroupTable.h"

namespace xlink2 {
GroupTable::GroupTable(s32 num_entries, sead::Heap* heap)
    : mCurrentIdx(0), mNumEntries(num_entries)
{
    mEntryBuffer = new (heap) Entry[num_entries];
}

} // namespace xlink2