#pragma once

#include <container/seadBuffer.h>

#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2TriggerCtrl.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class AlwaysTriggerCtrl : TriggerCtrl {
     ~AlwaysTriggerCtrl() override;
public:
    AlwaysTriggerCtrl(UserInstance* userInstance, sead::Buffer<ModelTriggerConnection>* buffer);

    void calc();
    void emitByTrigger_(int);
    void notifyActive();
private:
    u8 _0;
};
}