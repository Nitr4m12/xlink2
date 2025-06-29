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

void EnumPropertyDefinition::entry(s32 value, const char* key)
{
    Entry* buffer {mEntryBuffer};
    if (mTotalEntryNum > 0) {
        for (s64 i {0}; i < mTotalEntryNum; ++i, ++buffer) {
            if (strcmp(buffer->key, key) == 0)
                return;
        }
    }
    mEntryBuffer[mTotalEntryNum].key = key;
    mEntryBuffer[mTotalEntryNum].value = value;
    ++mTotalEntryNum;

}

s32 EnumPropertyDefinition::searchEntryValueByKey(const char* key) const
{
    if (mEntryBufferSize > 0) {
        for (s64 i {0}; i < mEntryBufferSize; ++i) {
            if (mEntryBuffer[i].key != nullptr && strcmp(mEntryBuffer[i].key, key) == 0)
                return mEntryBuffer[i].value;
        }
    }
    return -1;
}

const char* EnumPropertyDefinition::searchEntryKeyByValue(s32 value) const
{
    if (mEntryBufferSize > 0) {
        for (s64 i {0}; i < mEntryBufferSize; ++i) {
            if (mEntryBuffer[i].key != nullptr && mEntryBuffer[i].value == value)
                return mEntryBuffer[i].key;
        }
    }
    return "";
}

void EnumPropertyDefinition::setEntryBuf_(s32 buffer_size, Entry* buffer)
{
    mEntryBufferSize = buffer_size;
    mEntryBuffer = buffer;
}

}