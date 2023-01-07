#include "xlink2/xlink2AlwaysTriggerCtrl.h"

namespace xlink2 {
AlwaysTriggerCtrl::AlwaysTriggerCtrl(UserInstance* user_instance, sead::Buffer<ModelTriggerConnection>* buffer)
{
    mBuffer = buffer;
    mUserInstance = user_instance;
    _0 = 1;
};

void AlwaysTriggerCtrl::notifyActive()
{
    _0 = 1;
}
}