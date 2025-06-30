#include "xlink2/xlink2EnumPropertyDefinition.h"

namespace xlink2 {
EnumPropertyDefinition::EnumPropertyDefinition(const char* name, s32 num_entries, sead::Heap* heap, bool)
    : PropertyDefinition(name, PropertyType::Enum, 0)
{
    mCurrentIdx = 0;
    mNumEntry = num_entries;
    auto* buffer = new (heap) Entry[num_entries];
    mEntryBuffer = buffer;
}

EnumPropertyDefinition::EnumPropertyDefinition(const char* name, s32 num_entries, const char** key_buffer, bool b1, sead::Heap* heap)
    : EnumPropertyDefinition(name, num_entries, heap, b1)
{
    setEntries_(num_entries, key_buffer);
}

EnumPropertyDefinition::EnumPropertyDefinition(const char* name, bool)
    : PropertyDefinition(name, PropertyType::Enum, 0) 
{
    mCurrentIdx = 0;
    mNumEntry = 0;
    mEntryBuffer = nullptr;
}

void EnumPropertyDefinition::setEntries_(s32 entry_num, const char** key_buffer)
{
    if (entry_num > 0) {
        for (u32 i{0}, j{0}; i != entry_num; ++i, ++j) {
            mEntryBuffer[i].value = j;
            mEntryBuffer[i].key = key_buffer[j];
            ++mCurrentIdx;
        }
    }
}

void EnumPropertyDefinition::entry(s32 value, const char* key)
{
    Entry* buffer {mEntryBuffer};
    if (mCurrentIdx > 0) {
        for (s64 i {0}; i < mCurrentIdx; ++i, ++buffer) {
            if (strcmp(buffer->key, key) == 0)
                return;
        }
    }
    mEntryBuffer[mCurrentIdx].key = key;
    mEntryBuffer[mCurrentIdx].value = value;
    ++mCurrentIdx;

}

s32 EnumPropertyDefinition::getEntryKeyLength(u32 entry_idx) const
{
    const char* key {mEntryBuffer[entry_idx].key};
    s64 i {0};
    while (i < 64) {
        if (key[i] == '\0') return i;
        if (key[i + 1] == '\0') return i + 1;
        i += 2;
    }
    return -1;
}

s32 EnumPropertyDefinition::searchEntryValueByKey(const char* key) const
{
    if (mNumEntry > 0) {
        for (s64 i {0}; i < mNumEntry; ++i) {
            if (mEntryBuffer[i].key != nullptr && strcmp(mEntryBuffer[i].key, key) == 0)
                return mEntryBuffer[i].value;
        }
    }
    return -1;
}

const char* EnumPropertyDefinition::searchEntryKeyByValue(s32 value) const
{
    if (mNumEntry > 0) {
        for (s64 i {0}; i < mNumEntry; ++i) {
            if (mEntryBuffer[i].key != nullptr && mEntryBuffer[i].value == value)
                return mEntryBuffer[i].key;
        }
    }
    return "";
}

void EnumPropertyDefinition::setEntryBuf_(s32 buffer_size, Entry* buffer)
{
    mNumEntry = buffer_size;
    mEntryBuffer = buffer;
}

}