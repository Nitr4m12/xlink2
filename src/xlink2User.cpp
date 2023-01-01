#include "xlink2/xlink2User.h"

namespace xlink2 {

System* User::getSystem() const
{
    return mUserResource->getSystem();
}
}