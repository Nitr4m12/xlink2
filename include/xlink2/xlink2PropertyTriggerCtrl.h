#pragma once

#include "container/seadBuffer.h"
#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2ResProperty.h"
#include "xlink2/xlink2UserInstance.h"

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