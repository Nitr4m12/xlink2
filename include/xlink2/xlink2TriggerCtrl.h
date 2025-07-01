#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>

#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2TriggerType.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class TriggerCtrl {
public:
    virtual void calc() = 0;
    virtual ~TriggerCtrl() = default;

    void emitByTriggerImpl(TriggerType, s32, u32, ResAssetCallTable const*);
    void fadeByTrigger_(s32);
    ModelTriggerConnection* getModelTriggerConnection(s32 index);
    void resetIsOnceCheck_();
    void setBoneMatrixToConnection(u32, ModelTriggerConnection*);

protected:
    UserInstance* mUserInstance {nullptr};
    sead::Buffer<ModelTriggerConnection>* mConnectionBuffer {nullptr};
};
static_assert(sizeof(TriggerCtrl) == 0x18, "'xlink2::TriggerCtrl' is not of the correct size");

}  // namespace xlink2