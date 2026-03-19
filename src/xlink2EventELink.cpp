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

    auto* user_instance_callback {user_instance->getEventCallback()};
    if (user_instance_callback != nullptr) {
        IEventCallbackELink::EventArg arg {mpAssetCallTable, user_instance, nullptr, nullptr, this};
        user_instance_callback->eventCreate(arg);
    }
}

void EventELink::callEventDestroyCallback_()
{
    auto* system_callback {SystemELink::instance()->getEventCallback()};
    auto* user_instance {getUserInstanceELink()};
    if (system_callback != nullptr) {
        IEventCallbackELink::EventArg arg {mpAssetCallTable, user_instance, nullptr, nullptr, this};
        system_callback->eventDestroy(arg);
    }

    auto* user_instance_callback {user_instance->getEventCallback()};
    if (user_instance_callback != nullptr) {
        IEventCallbackELink::EventArg arg {mpAssetCallTable, user_instance, nullptr, nullptr, this};
        user_instance_callback->eventDestroy(arg);
    }
}

void EventELink::initializeImpl_()
{
    _17 = nullptr;
    mFlag1 = 0;
    mFlag2 = 0;
    mGroupId = -1;
}
} // namespace xlink2