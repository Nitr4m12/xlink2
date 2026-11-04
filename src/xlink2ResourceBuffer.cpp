#include "xlink2/xlink2ResourceBuffer.h"

#include <codec/seadHashCRC32.h>
#include <nn/util/util_BinTypes.h>

#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2ResourceParamCreator.h"
#include "xlink2/xlink2System.h"

namespace xlink2 {

namespace {

const u32 SignatureXLinkFile {nn::util::MakeSignature('X', 'L', 'N', 'K')};

}  // anonymous namespace

ResourceBuffer::ResourceBuffer()
{
    mParamDefineTable.reset();
}

ResourceBuffer::~ResourceBuffer() = default;

bool ResourceBuffer::load(void* bin, System* system)
{
    u8* ptr {static_cast<u8*>(bin)};

    u32* magic {static_cast<u32*>(bin)};
    if (*magic != SignatureXLinkFile)
        return false;

    auto* header {static_cast<ResourceHeader*>(bin)};
    if (header->version != system->getResourceVersion()) {
        system->addError(Error::Type::DataVersionError, nullptr, "Program:%d Resource:%d",
                         system->getResourceVersion(), header->version);
        return false;
    }

    if (mRomResourceParam.isInitialized || mParamDefineTable.isInitialized())
        return false;

    u64 num_user {static_cast<u64>(header->numUser)};
    ptr += num_user * 8;
    ptr += sizeof(ParamDefineTable);

    mParamDefineTable.setup(ptr, system->getUserParamNum(),
                            system->debugOperationParamOR().getPrintFlagCheck());
    ResourceParamCreator::createParamAndSolveResource(&mRomResourceParam, bin, &mParamDefineTable,
                                                      system);
    Locator::updateDataLoadedCount();
    return true;
}

ResUserHeader* ResourceBuffer::searchResUserHeader(const char* user_name) const
{
    if (!mRomResourceParam.isInitialized || mRomResourceParam.numUser == 0)
        return nullptr;

    u32 hash {sead::HashCRC32::calcStringHash(user_name)};

    u32 middle;

    u32 end {mRomResourceParam.numUser};
    u32 start {0};

    while (true) {
        middle = (start + end) / 2;

        u32 entry_hash {mRomResourceParam.nameHashTable[middle]};

        if (entry_hash == hash)
            return solveOffset<ResUserHeader>(mRomResourceParam.offsetTable[middle]);

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

void ResourceBuffer::applyGlobalPropertyDefinition(System* system)
{
    if (mRomResourceParam.isInitialized)
        ResourceParamCreator::solveAboutGlobalProperty(&mRomResourceParam, &mParamDefineTable,
                                                       system);
}
}  // namespace xlink2