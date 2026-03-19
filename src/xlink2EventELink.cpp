#include "xlink2/xlink2EventELink.h"

#include "xlink2/xlink2IEventCallbackELink.h"
#include "xlink2/xlink2SystemELink.h"

namespace xlink2 {
void EventELink::callEventCreateCallback_()
{
    auto* system_callback {SystemELink::instance()->getEventCallback()};
    auto* user_instance {getUserInstanceELink()};
    if (system_callback != nullptr) {
        IEventCallbackELink::EventArg arg {mpAssetCallTable, user_instance, nullptr, nullptr, this};
        system_callback->eventCreate(arg);
    }

    auto* instance_callback {user_instance->getEventCallback()};
    if (instance_callback != nullptr) {
        IEventCallbackELink::EventArg arg {mpAssetCallTable, user_instance, nullptr, nullptr, this};
        instance_callback->eventCreate(arg);
    }
}
} // namespace xlink2