#include "xlink2/xlink2TriggerCtrl.h"
#include "xlink2/xlink2ModelTriggerConnection.h"

namespace xlink2 {
void TriggerCtrl::fadeByTrigger_(s32 trigger_idx) {}

void TriggerCtrl::resetIsOnceCheck_() {
    if (mConnectionBuffer != nullptr && 0 < mConnectionBuffer->getSize()) {
        ModelTriggerConnection* model_trigger_connections {mConnectionBuffer->getBufferPtr()};
        for (s32 i{0}; i < mConnectionBuffer->size(); ++i)
            model_trigger_connections[i].isOnce = false;
    }
}

}  // namespace xlink2