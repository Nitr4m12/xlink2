#include "xlink2/xlink2EnumPropertyDefinition.h"
#include "xlink2/xlink2PropertyType.h"

namespace xlink2 {
void EnumPropertyDefinition::setEntries_(s32 entry_num, const char** key_buffer)
{
    if (entry_num > 0) {
        for (u32 i{0}, j{0}; i != entry_num; ++i, ++j) {
            mEntryBuffer[i].value = j;
            mEntryBuffer[i].key = key_buffer[j];
            ++mTotalEntryNum;
        }
    }
}
}