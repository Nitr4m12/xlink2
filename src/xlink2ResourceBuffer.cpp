#include <codec/seadHashCRC32.h>

#include "xlink2/xlink2ResourceBuffer.h"

#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2ResourceParamCreator.h"
#include "xlink2/xlink2System.h"

namespace xlink2 {
ResourceBuffer::ResourceBuffer()
{
    mParamDefineTable.reset();
}

ResourceBuffer::~ResourceBuffer() = default;

bool ResourceBuffer::load(void* bin, System* system)
{
    u32* magic {static_cast<u32*>(bin)};
    auto* header {static_cast<ResourceHeader*>(bin)};

    if (*magic == 0x4b4e4c58) {
        if (header->version != system->getResourceVersion()) {
            system->addError(Error::Type::DataVersionError, nullptr, "Program:%d Resource:%d", system->getResourceVersion(), header->version);
            return false;
        }

        if (!mRomResourceParam.isInitialized && !mParamDefineTable.isInitialized()) {
            u64 num_user {static_cast<u64>(header->numUser)};
            mParamDefineTable.setup(static_cast<u8*>(bin) + (num_user * 8) + sizeof(ParamDefineTable), system->getUserParamNum(), system->debugOperationParamOR().get258Check());
            ResourceParamCreator::createParamAndSolveResource(&mRomResourceParam, bin, &mParamDefineTable, system);
            Locator::updateDataLoadedCount();
            return true;
        }
        
        return false;
    }

    return false;
}

ResUserHeader* ResourceBuffer::searchResUserHeader(const char* user_name) const
{
    if (mRomResourceParam.isInitialized && mRomResourceParam.numUser != 0) {
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

void ResourceBuffer::applyGlobalPropertyDefinition(System* system) {
    if (mRomResourceParam.isInitialized)
        ResourceParamCreator::solveAboutGlobalProperty(&mRomResourceParam, &mParamDefineTable, system);
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