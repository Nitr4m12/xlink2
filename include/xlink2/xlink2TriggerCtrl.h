#pragma once

#include "basis/seadTypes.h"
#include "heap/seadHeap.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2TriggerType.h"
#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2ResMode.h"

namespace xlink2 {
class TriggerCtrl {
public:
    void emitByTriggerImpl(TriggerType, s32, u32, ResAssetCallTable const*);
    void fadeByTrigger(s32);
    void* getModelTriggerConnection(s32);
    void resetIsOnceCheck();
    void setBoneMatrixToConnection(u32, ModelTriggerConnection*);

private:
};
}  // namespace xlink2