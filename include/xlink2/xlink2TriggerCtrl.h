#pragma once

#include "basis/seadTypes.h"
#include "container/seadBuffer.h"
#include "heap/seadHeap.h"

#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2TriggerType.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class TriggerCtrl {
public:
    virtual void calc() = 0;
    virtual ~TriggerCtrl() = 0;

    void emitByTriggerImpl(TriggerType, s32, u32, ResAssetCallTable const*);
    void fadeByTrigger(s32);
    void* getModelTriggerConnection(s32);
    void resetIsOnceCheck_();
    void setBoneMatrixToConnection(u32, ModelTriggerConnection*);

protected:
    UserInstance* mUserInstance;
    sead::Buffer<ModelTriggerConnection>* mBuffer;
};
}  // namespace xlink2