#include <prim/seadPtrUtil.h>

#include "xlink2/xlink2TriggerCtrlMgr.h"

#include "xlink2/xlink2ActionTriggerCtrl.h"
#include "xlink2/xlink2AlwaysTriggerCtrl.h"
#include "xlink2/xlink2IUser.h"
#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2PropertyTriggerCtrl.h"
#include "xlink2/xlink2TriggerCtrlParam.h"
#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2UserResource.h"

namespace xlink2 {
TriggerCtrlMgr::TriggerCtrlMgr() = default;

void TriggerCtrlMgr::destroy()
{
    for (auto& param : mParams) {
        if (param != nullptr) {
            freeCtrlParam_(param);
            param = nullptr;
        }
    }
}

void TriggerCtrlMgr::initialize(s32 /*unused*/, s32 /*unused*/, sead::Heap* /*unused*/) {}

void TriggerCtrlMgr::freeCtrlParam_(TriggerCtrlParam* param)
{
    param->_0x0.freeBuffer();
    param->_0x10.freeBuffer();
    param->_0x20.freeBuffer();
    
    for (s32 i {0}; i < param->actionTriggerCtrlBuffer.size(); ++i) {
        if (param->actionTriggerCtrlBuffer[i] != nullptr) {
            delete param->actionTriggerCtrlBuffer[i];
            param->actionTriggerCtrlBuffer[i] = nullptr;
        }
    }
    param->actionTriggerCtrlBuffer.freeBuffer();
    
    for (s32 i {0}; i < param->localPropertyTriggerCtrlBuffer.size(); ++i) {
        if (param->localPropertyTriggerCtrlBuffer[i] != nullptr) {
            delete param->localPropertyTriggerCtrlBuffer[i];
            param->localPropertyTriggerCtrlBuffer[i] = nullptr;
        }
    }
    param->localPropertyTriggerCtrlBuffer.freeBuffer();

    for (s32 i {0}; i < param->globalPropertyTriggerCtrlBuffer.size(); ++i) {
        if (param->globalPropertyTriggerCtrlBuffer[i] != nullptr) {
            delete param->globalPropertyTriggerCtrlBuffer[i];
            param->globalPropertyTriggerCtrlBuffer[i] = nullptr;
        }
    }
    param->globalPropertyTriggerCtrlBuffer.freeBuffer();

    if (param->alwaysTriggerCtrl != nullptr) {
        delete param->alwaysTriggerCtrl;
        param->alwaysTriggerCtrl = nullptr;
    }
    
    param->allTriggerCtrls.freeBuffer();
    
    delete param;

}

void TriggerCtrlMgr::calc()
{
    if (getParam() != nullptr) {
        for (auto& trigger_ctrl : getParam()->allTriggerCtrls)
            trigger_ctrl.calc();
    }
}

void TriggerCtrlMgr::reset()
{
    TriggerCtrlParam* param {getParam()};
    if (param != nullptr) {
        for (s32 i {0}; i < param->actionTriggerCtrlBuffer.size(); ++i) {
            if (param->actionTriggerCtrlBuffer[i] != nullptr)
                param->actionTriggerCtrlBuffer[i]->reset();
        }

        for (s32 i {0}; i < param->localPropertyTriggerCtrlBuffer.size(); ++i) {
            if (param->localPropertyTriggerCtrlBuffer[i] != nullptr)
                param->localPropertyTriggerCtrlBuffer[i]->reset();
        }

        for (s32 i {0}; i < param->globalPropertyTriggerCtrlBuffer.size(); ++i) {
            if (param->globalPropertyTriggerCtrlBuffer[i] != nullptr)
                param->globalPropertyTriggerCtrlBuffer[i]->reset();
        }
    }

    mActionNeedToCalcFlag = 0;
}

const UserInstance* TriggerCtrlMgr::getUserInstance_() const
{
    return static_cast<UserInstance*>(sead::PtrUtil::addOffset(this, -offsetof(UserInstance, mTriggerCtrlMgr)));
}

void TriggerCtrlMgr::postChangeResource() {}

void TriggerCtrlMgr::changeAction(const char* name, s32 p2, s32 action_trigger_idx)
{
    s32 action_slot_num {getUserInstance_()->getUser()->getActionSlotNum()};
    if (getUserInstance_()->isDebugLogEnable(((DebugLogFlag)4))) {
        if (action_trigger_idx > -1 && action_trigger_idx < action_slot_num && getUserInstance_()->getUser()->getActionSlotNameTable() == nullptr) {
            getUserInstance_()->getIUser()->getActionSlotName(action_trigger_idx);
        }
        getUserInstance_()->getUser()->getSystem();
    }
    
    if (action_trigger_idx >= 0 && action_trigger_idx < action_slot_num) {
        TriggerCtrlParam* param {getParam()};
        if (param != nullptr && param->actionTriggerCtrlBuffer.isBufferReady()) {
            auto* action_trigger_ctrl {param->actionTriggerCtrlBuffer[action_trigger_idx]};
            if (action_trigger_ctrl != nullptr) {
                action_trigger_ctrl->changeAction(name, p2);
                updateActionNeedToCalcFlag_(action_trigger_idx);
            }
        }
    }
}

void TriggerCtrlMgr::updateActionNeedToCalcFlag_(s32 action_trigger_idx)
{
    auto* param {getParam()};
    s32 action_idx {param->actionTriggerCtrlBuffer[action_trigger_idx]->getCurrentResActionIdx()};

    if (action_idx >= 0) {
        auto* user_resource_param {getUserInstance_()->getUserResource()->getParam()};
        bool action_need_to_calc {user_resource_param->actionNeedToCalcBuffer[action_idx]};

        if (action_need_to_calc)
            mActionNeedToCalcFlag.setBit(action_trigger_idx);
        else
            mActionNeedToCalcFlag.resetBit(action_trigger_idx);
    }
    else {
        mActionNeedToCalcFlag.resetBit(action_trigger_idx);
    }
}

void TriggerCtrlMgr::changeAction(s32 p1, s32 p2, s32 action_trigger_idx)
{
    if (action_trigger_idx >= 0 && action_trigger_idx < getUserInstance_()->getUser()->getActionSlotNum()) {
        TriggerCtrlParam* param {getParam()};
        if (param != nullptr && param->actionTriggerCtrlBuffer.isBufferReady()) {
            auto* action_trigger_ctrl {param->actionTriggerCtrlBuffer[action_trigger_idx]};
            if (action_trigger_ctrl != nullptr) {
                action_trigger_ctrl->changeAction(p1, p2);
                updateActionNeedToCalcFlag_(action_trigger_idx);
            }
        }
    }
}

void TriggerCtrlMgr::setActionFrame(s32 frame, s32 action_trigger_idx)
{
    const UserInstance* user_instance {getUserInstance_()};

    if (action_trigger_idx >= 0 && user_instance->getUser()->getActionSlotNum() > action_trigger_idx) {
        TriggerCtrlParam* param {getParam()};
        if (param != nullptr && param->actionTriggerCtrlBuffer.isBufferReady()) {
            ActionTriggerCtrl* action_trigger_ctrl {param->actionTriggerCtrlBuffer[action_trigger_idx]};
            if (action_trigger_ctrl != nullptr)
                action_trigger_ctrl->setActionFrame(frame);
        }
    }
}

void TriggerCtrlMgr::stopAction(s32 action_trigger_idx)
{
    if (action_trigger_idx > -1 && action_trigger_idx < getUserInstance_()->getUser()->getActionSlotNum()) {
        TriggerCtrlParam* param {getParam()};
        if (param != nullptr && param->actionTriggerCtrlBuffer.isBufferReady()) {
            auto* action_trigger_ctrl {param->actionTriggerCtrlBuffer[action_trigger_idx]};
            if (action_trigger_ctrl != nullptr) {
                action_trigger_ctrl->stopAction();
                updateActionNeedToCalcFlag_(action_trigger_idx);
            }
        }
    }
}

// NON-MATCHING
bool TriggerCtrlMgr::isCurrentActionNeedToObserve(s32 action_trigger_idx) const
{
    bool need_to_observe {false};
    if (action_trigger_idx > -1 && action_trigger_idx < getUserInstance_()->getUser()->getActionSlotNum()) {
        auto* param {getParam()};
        if (param != nullptr && param->actionTriggerCtrlBuffer.isBufferReady()) {
            auto* action_trigger_ctrl {param->actionTriggerCtrlBuffer[action_trigger_idx]};
            if (action_trigger_ctrl != nullptr)
                need_to_observe = action_trigger_ctrl->isActive();
        }
    }

    return need_to_observe;
}

s32 TriggerCtrlMgr::getCurrentResActionIdx(s32 action_trigger_idx) const
{
    if (action_trigger_idx >= 0 && getUserInstance_()->getUser()->getActionSlotNum() > action_trigger_idx) {
        TriggerCtrlParam* param {getParam()};
        if (param != nullptr && param->actionTriggerCtrlBuffer.isBufferReady()) {
            ActionTriggerCtrl* action_trigger_ctrl {param->actionTriggerCtrlBuffer[action_trigger_idx]};
            if (action_trigger_ctrl != nullptr)
                return action_trigger_ctrl->getCurrentResActionIdx();
        }
    }
    return -1;
}

// NON-MATCHING: instruction missing
void TriggerCtrlMgr::notifyActive()
{
    if (getParam() != nullptr) {
        s16 action_slot_num {getUserInstance_()->getUser()->getActionSlotNum()};
        for (s32 i {0}; i < action_slot_num; ++i) {
            ActionTriggerCtrl* action_trigger_ctrl {getParam()->actionTriggerCtrlBuffer[i]};
            if (action_trigger_ctrl != nullptr)
                action_trigger_ctrl->notifyActive();
        }

        if (getParam()->alwaysTriggerCtrl != nullptr)
            getParam()->alwaysTriggerCtrl->notifyActive();
    }
}

s32 TriggerCtrlMgr::getCurrentActionFrame([[maybe_unused]] s32 action_idx) const 
{
    return -1;
}

const char* TriggerCtrlMgr::getCurrentActionName([[maybe_unused]] s32 action_idx) const 
{
    return nullptr;
}

void TriggerCtrlMgr::resetAllModelTriggerConnection()
{
    if (getParam() != nullptr) {
        for (s32 i {0}; i < getParam()->_0x0.size(); ++i)
            getParam()->_0x0[i].isActive = false;

        for (s32 i {0}; i < getParam()->_0x10.size(); ++i)
            getParam()->_0x10[i].isActive = false;

        for (s32 i {0}; i < getParam()->_0x20.size(); ++i)
            getParam()->_0x20[i].isActive = false;
    }
}

}  // namespace xlink2