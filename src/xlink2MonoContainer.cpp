#include "xlink2/xlink2MonoContainer.h"

namespace xlink2 {
MonoContainer::~MonoContainer() = default;

bool MonoContainer::killOneTimeEvent()
{
    if (mpChild != nullptr && !mpChild->killOneTimeEvent()) {
        kill();
        return true;
    }
    return false;
}
}