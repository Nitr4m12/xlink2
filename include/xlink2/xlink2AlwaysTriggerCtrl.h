#pragma once

#include <container/seadBuffer.h>
#include "xlink2/xlink2.h"

namespace xlink2 {
class AlwaysTriggerCtrl {
    ~AlwaysTriggerCtrl();
public:
    AlwaysTriggerCtrl(UserInstance* userInstance, sead::Buffer<ModelTriggerConnection>* buffer);

    void calc();
    void emitByTrigger_(int);
    void notifyActive();
private:
    UserInstance* mUserInstance;
    sead::Buffer<ModelTriggerConnection>* mBuffer;
};
}