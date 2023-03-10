#pragma once

#include <container/seadBuffer.h>

#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2TriggerCtrl.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class AlwaysTriggerCtrl : TriggerCtrl {
    ~AlwaysTriggerCtrl() override;

public:
    AlwaysTriggerCtrl(UserInstance* user_instance, sead::Buffer<ModelTriggerConnection>* buffer);

    void calc() override;
    void emitByTrigger_(int);
    void notifyActive();

private:
    u8 _0;
};
}  // namespace xlink2