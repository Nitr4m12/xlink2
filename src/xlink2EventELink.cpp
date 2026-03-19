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
    mDelayEmitParam._0xf8 = nullptr;
    mDelayEmitParam.isFixedFlag = 0;
    mDelayEmitParam.flag2 = 0;
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
    if (!mDelayEmitParam.isFixedFlag.isZero()) {
        DelayEmitParam* delay_param {&mDelayEmitParam};
        mDelayEmitParam.flag2 = mDelayEmitParam.isFixedFlag | mDelayEmitParam.flag2;
        for (auto& executor : mAliveAssetExecutors) {
            auto* executor_elink {static_cast<AssetExecutorELink*>(&executor)};
            executor_elink->setDelayParam(delay_param, mDelayEmitParam.isFixedFlag);
        }

        for (auto& executor : mFadeBySystemAssetExecutors) {
            auto* executor_elink {static_cast<AssetExecutorELink*>(&executor)};
            executor_elink->setDelayParam(delay_param, mDelayEmitParam.isFixedFlag);
        }
        mDelayEmitParam.isFixedFlag.makeAllZero();
    }
}
} // namespace xlink2