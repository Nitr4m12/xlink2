#include "xlink2/xlink2TriggerCtrl.h"

namespace xlink2 {
void TriggerCtrl::fadeByTrigger_(s32 idx) 
{
    constexpr const char* TRIGGERTYPES[3] {"Action", "Property", "Always"};

    Handle* handle {&mConnectionBuffer->unsafeGet(idx)->handle};
    Event* event {static_cast<Event*>(handle->get0())};
    if (event != nullptr && event->getCreateId() == handle->getCreateId()) {
        mUserInstance->printLogFadeOrKill(event, "fadeBySystem by %s Trigger", TRIGGERTYPES[(s32)event->getTriggerType()]);
        event->fadeBySystem();
        handle->reset();
    }
}

ModelTriggerConnection* TriggerCtrl::getModelTriggerConnection_(s32 idx)
{
    if (mConnectionBuffer != nullptr && mConnectionBuffer->getSize() > idx)
        return mConnectionBuffer->get(idx);
    
    return nullptr;
}

void TriggerCtrl::resetIsOnceCheck_() 
{
    if (mConnectionBuffer != nullptr && 0 < mConnectionBuffer->getSize()) {
        ModelTriggerConnection* model_trigger_connections {mConnectionBuffer->getBufferPtr()};
        for (s32 i{0}; i < mConnectionBuffer->getSize(); ++i)
            model_trigger_connections[i].isActive = false;
    }
}

}  // namespace xlink2