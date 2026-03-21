#include <xlink2/xlink2UserResourceELink.h>

namespace xlink2 {
// SystemELink* UserResourceELink::getSystem() const {
//     return SystemELink::sInstance;
// }
const ResourceAccessorELink& UserResourceELink::getAccessor() const
{
    return mAccessor;
}
}