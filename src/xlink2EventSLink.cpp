#include "xlink2/xlink2EventSLink.h"

namespace xlink2 {
void EventSLink::initializeImpl_() {}

const sead::Vector3f& EventSLink::getVelocity() const
{
    return mVelocity;
}
} // namespace xlink2