#include <xlink2/xlink2ResourceBuffer.h>
#include "codec/seadHashCRC32.h"
#include "xlink2/xlink2ResUserHeader.h"
#include "xlink2/xlink2ResourceParamCreator.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
ResourceBuffer::~ResourceBuffer() = default;

void ResourceBuffer::applyGlobalPropertyDefinition(System* system) {
    if (mRomResourceParam.isInitialized) {
        ResourceParamCreator::solveAboutGlobalProperty(&mRomResourceParam, &mParamDefineTable,
                                                              system);
    }
}

ResUserHeader* ResourceBuffer::searchResUserHeader(const char* user_name) const
{
    if (mRomResourceParam.isInitialized && mRomResourceParam.numUser != 0) {
        // Based on binarySearch_ from seadSharcArchiveRes.cpp

        u32 hash {sead::HashCRC32::calcStringHash(user_name)};

        u32 middle;
        
        u32 end = mRomResourceParam.numUser;
        u32 start {0};

        while (true) {
            middle = (start + end) / 2;

            u32 entry_hash {mRomResourceParam.nameHashTable[middle]};

            if (entry_hash == hash)
                return calcOffset<ResUserHeader>(mRomResourceParam.offsetTable[middle]);

            if (entry_hash < hash) {
                if (start == middle)
                    return nullptr;
    
                start = middle;
            }
            else {
                if (end == middle)
                    return nullptr;

                end = middle;
            }
        }
    }

    return nullptr;
}

RomResourceParam ResourceBuffer::getEmptyRomResourceParam() {
    static RomResourceParam sDummy{};
    return sDummy;
}

ResUserHeader ResourceBuffer::getEmptyUserHeader() {
    static ResUserHeader sDummy{};
    return sDummy;
}
}  // namespace xlink2