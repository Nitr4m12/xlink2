#include "xlink2/xlink2ActionTriggerCtrl.h"
#include <cstring>
#include "codec/seadHashCRC32.h"
#include "xlink2/xlink2UserResourceParam.h"
#include "xlink2/xlink2Util.h"

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

void ActionTriggerCtrl::reset() 
{
    mAction = nullptr;
    mUserInfo.mNameHash = 0;
    mUserInfo.mOffset = 0;
    mUserBinPos = 0;
    mIsActive = false;
}

void ActionTriggerCtrl::calc() {}

TriggerType ActionTriggerCtrl::getActionTriggerType_(const ResActionTrigger& action_trigger) 
{
    if (action_trigger.flag.isOnBit(2))
        return TriggerType::Property;

    if (action_trigger.flag.isOnBit(3))
        return TriggerType::Always;

    if (action_trigger.flag.isOnBit(4))
        return TriggerType::None;

    return TriggerType::Action;
}

void ActionTriggerCtrl::emitByTrigger_(s32 action_trigger_idx) 
{
    ResActionTrigger* action_trigger {getUserResource()->getActionTriggerTableItem(action_trigger_idx)};

    if (!(action_trigger->flag & 1) || !getModelTriggerConnection(action_trigger_idx)->isActive) {
        u32 ow_param_pos {action_trigger->overwriteParamPos};
        ResAssetCallTable* asset_ctb {calcOffset<ResAssetCallTable>(action_trigger->assetCtbPos)};
        emitByTriggerImpl(TriggerType::Action, action_trigger_idx, ow_param_pos, asset_ctb);
        getModelTriggerConnection(action_trigger_idx)->isActive = true;
    }
}

void ActionTriggerCtrl::notifyActive() 
{
    if (mAction != nullptr) {
        for (int i {mAction->triggerStartIdx}; i <= mAction->triggerEndIdx; i++) {
            getModelTriggerConnection(i)->isActive = false;
        }
    }
}

// NON-MATCHING / WIP
void ActionTriggerCtrl::changeAction(const char* name, s32 p2) 
{
    ResAction* action {searchResAction_(mActionSlot, name, nullptr)};
    if (action == nullptr)
        stopAction();
    else if (mAction != action)
        changeActionImpl_(action, p2, getUserResource());

    mUserInfo.mNameHash = sead::HashCRC32::calcStringHash(name);
}

ResAction* ActionTriggerCtrl::searchResAction_(const ResActionSlot* action_slot, const char* name, s32* idx)  const
{
    if (action_slot->actionStartIdx < 0)
        return nullptr;
    
    UserResourceParam* user_res_param = getUserResource()->getParam();

    ResAction* actionTable = user_res_param->resActionTable;
    for (s32 i = action_slot->actionStartIdx; i <= action_slot->actionEndIdx; ++i) {
        if (strcmp(calcOffset<const char>(actionTable[i].namePos), name) == 0) {
            if (idx != nullptr)
                *idx = i;
            return actionTable + i;
        }
    }
    return nullptr;
}

// NON-MATCHING
void ActionTriggerCtrl::stopAction() 
{
    if (mAction != nullptr) {
        UserResourceParam* user_res_param {getUserResource()->getParam()};
        if (mAction->triggerStartIdx <= mAction->triggerEndIdx) {
            for (int i {mAction->triggerStartIdx - 1}; i < mAction->triggerEndIdx; ++i) {
                sead::BitFlag16 action_flag {user_res_param->resActionTriggerTable[i].flag};
                fadeByTrigger_(i);
                if ((action_flag - 4) == -1 || (action_flag & 12) == 8)
                    emitByTrigger_(i);
            }
        }
        mAction = nullptr;
        mIsActive = false;
    }
}

void ActionTriggerCtrl::changeAction(s32 action_idx, s32 p2) 
{
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

s32 ActionTriggerCtrl::getCurrentResActionIdx() const 
{
    if (mAction != nullptr) {
        UserResourceParam* param {getUserResource()->getParam()};
        return mAction - param->resActionTable;
    }

    return -1;
}

ActionTriggerCtrl::~ActionTriggerCtrl() = default;
}  // namespace xlink2