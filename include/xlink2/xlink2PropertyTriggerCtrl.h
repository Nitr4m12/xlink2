#pragma once

#include "container/seadBuffer.h"
#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2ResProperty.h"
#include "xlink2/xlink2TriggerCtrl.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class PropertyTriggerCtrl : TriggerCtrl {
    virtual ~PropertyTriggerCtrl();

public:
    PropertyTriggerCtrl(UserInstance*, sead::Buffer<ModelTriggerConnection>*, s32, bool,
                        ResProperty const*, ResMode);
    void calc();
    void reset();

private:
    UserInstance* mUserInstance;
    sead::Buffer<ModelTriggerConnection>* mBuffer;
    ResProperty* mResProperty;

};
}  // namespace xlink2