#pragma once

#include "container/seadBuffer.h"
#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2ResProperty.h"
#include "xlink2/xlink2TriggerCtrl.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class PropertyTriggerCtrl : TriggerCtrl {
    ~PropertyTriggerCtrl() override;

public:
    PropertyTriggerCtrl(UserInstance*, sead::Buffer<ModelTriggerConnection>*, s32, bool,
                        ResProperty const*, ResMode);
    void calc();
    void reset();

private:
    ResProperty* mResProperty;
    s32 _0;
    u32 _1;
    u8 _2;
    bool _3;
};
}  // namespace xlink2