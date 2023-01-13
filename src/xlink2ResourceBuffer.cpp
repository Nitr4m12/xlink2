#include "xlink2/xlink2ResourceBuffer.h"

namespace xlink2 {
void ResourceBuffer::applyGlobalPropertyDefinition(System* system) {
    if (_20 != 0) {
        return ResourceParamCreator::solveAboutGlobalProperty(mRomResourceParam, mParamDefineTable,
                                                              system);
    }
}
}  // namespace xlink2