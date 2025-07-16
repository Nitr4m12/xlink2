#include "xlink2/xlink2TriggerCtrl.h"

#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2Handle.h"
#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
void TriggerCtrl::fadeByTrigger_(s32 idx) 
{
    constexpr const char* TRIGGERTYPES[3] {"Action", "Property", "Always"};

    Handle* handle {&mConnectionBuffer->unsafeGet(idx)->handle};
    Event* event {handle->getEvent()};
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
    if (mConnectionBuffer != nullptr)
        for (auto it {mConnectionBuffer->begin()}; it != mConnectionBuffer->end(); ++it)
            mConnectionBuffer->getBufferPtr()[it.getIndex()].isActive = false;
}

}  // namespace xlink2