#include "xlink2/xlink2AlwaysTriggerCtrl.h"

namespace xlink2 {
AlwaysTriggerCtrl::AlwaysTriggerCtrl(UserInstance* userInstance, sead::Buffer<ModelTriggerConnection>* buffer)
{
    mUserInstance = userInstance;
    mBuffer = buffer;
    _0 = 1;
};
}