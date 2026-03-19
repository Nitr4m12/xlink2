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

void EventELink::doFinalize_()
{
    callEventDestroyCallback_();
    if (mBitFlag.isOffBit(2))
        fixDelayParam_();
}

void EventELink::fixDelayParam_()
{
    if (!mFlag1.isZero()) {
        DelayEmitParam* delay_param {&mDelayEmitParam};
        mFlag2 = mFlag1 | mFlag2;
        for (auto& executor : mAliveAssetExecutors) {
            auto* executor_elink {static_cast<AssetExecutorELink*>(&executor)};
            executor_elink->setDelayParam(delay_param, mFlag1);
        }

        for (auto& executor : mFadeBySystemAssetExecutors) {
            auto* executor_elink {static_cast<AssetExecutorELink*>(&executor)};
            executor_elink->setDelayParam(delay_param, mFlag1);
        }
        mFlag1.makeAllZero();
    }
}
} // namespace xlink2