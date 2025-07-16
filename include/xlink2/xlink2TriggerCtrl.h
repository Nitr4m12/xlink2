#pragma once

#include <container/seadBuffer.h>

#include "xlink2/xlink2Resource.h"

namespace xlink2 {
struct ModelTriggerConnection;
class UserInstance;
class TriggerCtrl {
public:
    virtual void calc() = 0;
    virtual ~TriggerCtrl() = default;

    void emitByTriggerImpl_(TriggerType, s32, u32, const ResAssetCallTable*);
    void fadeByTrigger_(s32);

    ModelTriggerConnection* getModelTriggerConnection_(s32 idx);

    void resetIsOnceCheck_();

    void setBoneMatrixToConnection(u32, ModelTriggerConnection*);

protected:
    UserInstance* mUserInstance {nullptr};
    sead::Buffer<ModelTriggerConnection>* mConnectionBuffer {nullptr}; // unsure
};
static_assert(sizeof(TriggerCtrl) == 0x18, "xlink2::TriggerCtrl size mismatch");

}  // namespace xlink2