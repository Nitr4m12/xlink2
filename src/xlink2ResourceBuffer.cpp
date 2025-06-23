#include <xlink2/xlink2ResourceBuffer.h>

namespace xlink2 {
ResourceBuffer::~ResourceBuffer() = default;

// void ResourceBuffer::applyGlobalPropertyDefinition(System* system) {
//     if (_20 != 0) {
//         return ResourceParamCreator::solveAboutGlobalProperty(&mRomResourceParam, &mParamDefineTable,
//                                                               system);
//     }
// }

RomResourceParam ResourceBuffer::getEmptyRomResourceParam() {
    static RomResourceParam sDummy{};
    return sDummy;
}

ResUserHeader ResourceBuffer::getEmptyUserHeader() {
    static ResUserHeader sDummy{};
    return sDummy;
}
}  // namespace xlink2