#include "xlink2/xlink2ActionTriggerCtrl.h"

namespace xlink2 {

ActionTriggerCtrl::ActionTriggerCtrl(UserInstance* user_instance,
                                     sead::Buffer<ModelTriggerConnection>* connection_buffer,
                                     const ResActionSlot* action_slot)
{
    mConnectionBuffer = connection_buffer;
    mActionSlot = action_slot;
    mUserInstance = user_instance;
    mUserInfo.mOffset = 0;
    mUserInfo.mNameHash = 0;
    mUserBinPos = 0;
    mAction = nullptr;
    mIsActive = false;
}

void ActionTriggerCtrl::reset() {
    mAction = nullptr;
    mUserBinPos = 0;
    mIsActive = false;
}
}  // namespace xlink2