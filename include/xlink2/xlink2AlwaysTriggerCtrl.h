#pragma once

#include <container/seadBuffer.h>

#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class AlwaysTriggerCtrl {
    virtual ~AlwaysTriggerCtrl();
public:
    AlwaysTriggerCtrl(UserInstance* userInstance, sead::Buffer<ModelTriggerConnection>* buffer);

    void calc();
    void emitByTrigger_(int);
    void notifyActive();
private:
    UserInstance* mUserInstance;
    sead::Buffer<ModelTriggerConnection>* mBuffer;
    u8 _0;
};
}