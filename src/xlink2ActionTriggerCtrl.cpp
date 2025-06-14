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
    mUserInfo.mNameHash = 0;
    mUserInfo.mOffset = 0;
    mUserBinPos = 0;
    mIsActive = false;
}

void ActionTriggerCtrl::calc() {
}

TriggerType ActionTriggerCtrl::getActionTriggerType_(const ResActionTrigger& action_trigger) {}

void ActionTriggerCtrl::changeAction(s32 action_idx, s32 p2) {

    UserResource* user_resource {getUserResource()};
    UserResourceParam* user_resource_param {user_resource->getParam()};
   
    if (-1 < action_idx && action_idx < (s32)user_resource_param->resUserHeader->numResAction) { 
        ResAction* res_action = &user_resource_param->resActionTable[action_idx];
        if (mAction != res_action) {
            changeActionImpl_(res_action, p2, user_resource);
        }
        return;
    }
    stopAction();
}


}  // namespace xlink2