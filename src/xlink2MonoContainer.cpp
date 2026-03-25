#include "xlink2/xlink2MonoContainer.h"
#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2Event.h"

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

void MonoContainer::kill()
{
    if (mpChild != nullptr) {
        auto* event {mpEvent};
        auto* child_executor {reinterpret_cast<AssetExecutor*>(mpChild)};
        mpChild = nullptr;
        event->getAliveAssetExecutors().erase(child_executor);
        event->getFadeBySystemExecutors().pushBack(child_executor);
        child_executor->kill();
    }

    mAssetDuration = 0;
    _1 = -1.0f;
}
} // namespace xlink2