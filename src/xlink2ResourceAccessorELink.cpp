#include <xlink2/xlink2ResourceAccessorELink.h>
#include <xlink2/xlink2ResourceUtil.h>

namespace xlink2 {
f32 ResourceAccessorELink::getOverwriteAlpha(u32 p1, const UserInstance* p2) const {
    return ResourceAccessor::getResOverwriteParamValueFloat(p1, 0x16, p2);
}

char* ResourceAccessorELink::getOverwriteBoneName(u32 p1) const {
    return ResourceAccessor::getResOverwriteParamValueString(p1, 0xb);
}

f32 ResourceAccessorELink::getOverwriteColorBlue(u32 p1, const UserInstance* p2) const {
    return ResourceAccessor::getResOverwriteParamValueFloat(p1, 0x15, p2);
}

f32 ResourceAccessorELink::getOverwriteColorGreen(u32 p1, const UserInstance* p2) const {
    return ResourceAccessor::getResOverwriteParamValueFloat(p1, 0x14, p2);
}

f32 ResourceAccessorELink::getOverwriteColorRed(u32 p1, const UserInstance* p2) const {
    return ResourceAccessor::getResOverwriteParamValueFloat(p1, 0x13, p2);
}

bool ResourceAccessorELink::isBoneNameOverwritten(u32 p1) const {
    return isParamOverwritten(p1, 0xb);
}
}  // namespace xlink2