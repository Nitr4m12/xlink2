#include "xlink2/xlink2TriggerCtrl.h"

namespace xlink2 {
void TriggerCtrl::fadeByTrigger_(s32 trigger_idx) {}

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