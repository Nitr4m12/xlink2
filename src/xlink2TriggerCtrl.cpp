#include "xlink2/xlink2TriggerCtrl.h"

namespace xlink2 {
void TriggerCtrl::fadeByTrigger_(s32 param)
{
    const auto* trigger = mConnectionBuffer->getBufferPtr();
    Event* event = trigger[param].mEvent;
    if (event && trigger[param]._2 == event->get3()) {
        mUserInstance->printLogFadeOrKill(event, "fadeBySystem by %s Trigger", event->getTriggerType());
        event->fadeBySystem();
    }
}
}  // namespace xlink2