#include <cstring>
#include <codec/seadHashCRC32.h>

#include "xlink2/xlink2ActionTriggerCtrl.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2ResourceUtil.h"
#include "xlink2/xlink2UserResource.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
ActionTriggerCtrl::ActionTriggerCtrl(UserInstance* user_instance,
                                     sead::Buffer<ModelTriggerConnection>* connection_buffer,
                                     const ResActionSlot* action_slot)
    : TriggerCtrl(user_instance, connection_buffer)
{
    mConnectionBuffer = connection_buffer;
    mActionSlot = action_slot;
    mUserInstance = user_instance;
    mActionFrame = 0;
    mNameHash = 0;
    mEndActionFrame = 0;
    mpAction = nullptr;
    mIsActive = false;
}

ActionTriggerCtrl::~ActionTriggerCtrl() = default;

void ActionTriggerCtrl::reset() 
{
    mpAction = nullptr;
    mNameHash = 0;
    mActionFrame = 0;
    mEndActionFrame = 0;
    mIsActive = false;
}

// NON-MATCHING
void ActionTriggerCtrl::calc() 
{
    if (mpAction != nullptr) {
        UserResourceParam* user_resource_param {getUserResource()->getParamWithSetupCheck()};
        if (user_resource_param != nullptr) {
            if (mActionFrame > mEndActionFrame) {
                mEndActionFrame = -1;
            }

            user_resource_param = getUserResource()->getParam();
            ResActionTrigger* action_trigger_table {user_resource_param->userBinParam.pResActionTriggerTable};
            for (s32 i {mpAction->triggerStartIdx}; i <= mpAction->triggerEndIdx; ++i) {
                ModelTriggerConnection* mtc {mConnectionBuffer->get(i)};
                s32 j {1};
                if (!(action_trigger_table[i].flag & 12)) {
                    j = 3;
                    if (!(action_trigger_table[i].flag & 16))
                        j = 0;
                }

                const ResourceAccessor& accessor {getUserResource()->getAccessor()};
                auto* asset_ctb {solveOffset<ResAssetCallTable>(action_trigger_table[i].assetCtbPos)};

                bool need_observe {accessor.isNeedObserve(*asset_ctb)};
                if (j == 0 || need_observe) {
                    if (mActionFrame > mEndActionFrame && action_trigger_table[i].flag.isOffBit(0) && mtc->isActive) {
                        fadeByTrigger_(i);
                    }
                    
                    if (need_observe) {
                        if (action_trigger_table[i].startFrame >= mActionFrame && 
                            action_trigger_table[i].endFrame < mActionFrame && 
                            (mtc->handle.getEvent() == nullptr || mtc->handle.getEvent()->getCreateId() != mtc->handle.getCreateId())) {
                            emitByTrigger_(i);
                        }
                    }
                    else if (action_trigger_table[i].startFrame <= mEndActionFrame &&
                             action_trigger_table[i].startFrame <= mActionFrame && 
                             action_trigger_table[i].endFrame > mActionFrame) {
                            emitByTrigger_(i);
                    }

                    if (mEndActionFrame < action_trigger_table[i].endFrame && mActionFrame >= action_trigger_table[i].endFrame)
                        fadeByTrigger_(i);
                }
            }
        }
    }

    mEndActionFrame = mActionFrame;
}

TriggerType ActionTriggerCtrl::getActionTriggerType_(const ResActionTrigger& action_trigger) 
{
    return ResourceUtil::getActionTriggerType(action_trigger);
}

void ActionTriggerCtrl::emitByTrigger_(s32 action_trigger_idx) 
{
    ResActionTrigger* action_trigger {getUserResource()->getActionTriggerTableItem(action_trigger_idx)};

    if (!action_trigger->flag.isOn(1) || !getModelTriggerConnection_(action_trigger_idx)->isActive) {
        s32 ow_param_pos {action_trigger->overwriteParamPos};
        ResAssetCallTable* asset_ctb {solveOffset<ResAssetCallTable>(action_trigger->assetCtbPos)};
        emitByTriggerImpl_(TriggerType::Action, action_trigger_idx, ow_param_pos, asset_ctb);
        getModelTriggerConnection_(action_trigger_idx)->isActive = true;
    }
}

void ActionTriggerCtrl::notifyActive() 
{
    if (mpAction != nullptr) {
        for (int i {mpAction->triggerStartIdx}; i <= mpAction->triggerEndIdx; i++) {
            getModelTriggerConnection_(i)->isActive = false;
        }
    }
}

void ActionTriggerCtrl::changeAction(const char* name, s32 p2) 
{
    ResAction* action {searchResAction_(mActionSlot, name, nullptr)};
    if (action == nullptr)
        stopAction();
    else if (mpAction != action)
        changeActionImpl_(action, p2, getUserResource());

    mNameHash = sead::HashCRC32::calcStringHash(name);
}

ResAction* ActionTriggerCtrl::searchResAction_(const ResActionSlot* action_slot, const char* name, s32* idx)  const
{
    if (action_slot->actionStartIdx < 0)
        return nullptr;
    
    UserResourceParam* user_res_param = getUserResource()->getParam();

    ResAction* action_table = user_res_param->userBinParam.pResActionTable;
    for (s32 i = action_slot->actionStartIdx; i <= action_slot->actionEndIdx; ++i) {
        if (strcmp(solveOffset<const char>(action_table[i].namePos), name) == 0) {
            if (idx != nullptr)
                *idx = i;
            return action_table + i;
        }
    }
    return nullptr;
}

void ActionTriggerCtrl::stopAction() 
{
    if (mpAction == nullptr)
        return;

    UserResourceParam* user_res_param {getUserResource()->getParam()};
    
    ResActionTrigger* action_trigger_table {user_res_param->userBinParam.pResActionTriggerTable};
    for (s32 i {mpAction->triggerStartIdx}; i <= mpAction->triggerEndIdx; ++i) {
        fadeByTrigger_(i);
        if (action_trigger_table[i].startFrame == -1 || (action_trigger_table[i].flag & 12) == 8)
            emitByTrigger_(i);
    }
    mpAction = nullptr;
    mIsActive = false;
}

void ActionTriggerCtrl::changeAction(s32 action_idx, s32 p2) 
{
    UserResource* user_resource {getUserResource()};
    UserResourceParam* user_resource_param {user_resource->getParam()};
   
    if (-1 < action_idx && action_idx < static_cast<s32>(user_resource_param->userBinParam.pResUserHeader->numResAction)) { 
        ResAction* res_action = &user_resource_param->userBinParam.pResActionTable[action_idx];
        if (mpAction != res_action) {
            changeActionImpl_(res_action, p2, user_resource);
        }
        return;
    }
    stopAction();
}

s32 ActionTriggerCtrl::getCurrentResActionIdx() const 
{
    if (mpAction != nullptr) {
        UserResourceParam* param {getUserResource()->getParam()};
        return mpAction - param->userBinParam.pResActionTable;
    }

    return -1;
}

void ActionTriggerCtrl::restartAction(const char* name, s32 idx) 
{
    if (mActionSlot != nullptr) {
        ResAction* action {searchResAction_(mActionSlot, name, nullptr)};
        if (action) {
            mpAction = action;
            mActionFrame = idx;
            mEndActionFrame = idx;
        }
    }
}
}  // namespace xlink2