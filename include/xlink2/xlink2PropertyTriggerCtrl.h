#pragma once

#include "container/seadBuffer.h"
#include "xlink2/xlink2.h"

namespace xlink2 {
class PropertyTriggerCtrl {
    virtual ~PropertyTriggerCtrl();

public:
    PropertyTriggerCtrl(UserInstance*, sead::Buffer<ModelTriggerConnection>*, s32, bool,
                        ResProperty const*, ResMode);
    void calc();
    void reset();

private:
};
}  // namespace xlink2