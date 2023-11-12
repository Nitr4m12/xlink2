#pragma once

#include "xlink2/xlink2TriggerCtrl.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
class AlwaysTriggerCtrl : TriggerCtrl {
public:
    AlwaysTriggerCtrl(UserInstance* user_instance, sead::Buffer<ModelTriggerConnection>* buffer);

    void calc() override;
    void emitByTrigger_(s32);
    void notifyActive();

    ~AlwaysTriggerCtrl() override;

private:
    bool mIsActive{true};
};
static_assert(sizeof(AlwaysTriggerCtrl) == 0x20, "Wrong size for 'xlink2::AlwaysTriggerCtrl'");

}  // namespace xlink2