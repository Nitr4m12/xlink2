#pragma once

#include "container/seadBuffer.h"

#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2TriggerCtrl.h"

namespace xlink2 {
class PropertyTriggerCtrl : TriggerCtrl {
    
public:
    PropertyTriggerCtrl(UserInstance*, sead::Buffer<ModelTriggerConnection>*, s32, bool,
                        const ResProperty*, ResMode);
    ~PropertyTriggerCtrl() override;

    void reset();
    void calc() override;

private:
    const ResProperty* mResProperty {};
    s32 mPropertyIndex {0};
    PropertyValueType mPropertyValue {};
    bool _2 {true};
    bool mIsGlobalProperty {};
};
static_assert(sizeof(PropertyTriggerCtrl) == 0x30, "xlink2::PropertyTriggerCtrl size mismatch");

}  // namespace xlink2