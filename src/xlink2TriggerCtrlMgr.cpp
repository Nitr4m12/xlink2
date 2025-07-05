#include <prim/seadPtrUtil.h>

#include "xlink2/xlink2TriggerCtrlMgr.h"
#include "xlink2/xlink2ActionTriggerCtrl.h"
#include "xlink2/xlink2AlwaysTriggerCtrl.h"
#include "xlink2/xlink2PropertyTriggerCtrl.h"
#include "xlink2/xlink2TriggerCtrlParam.h"
#include "xlink2/xlink2UserInstance.h"

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
    
    for (s32 i {0}; i < param->actionTriggerCtrlBuffer.getSize(); ++i) {
        if (param->actionTriggerCtrlBuffer[i] != nullptr) {
            delete param->actionTriggerCtrlBuffer[i];
            param->actionTriggerCtrlBuffer[i] = nullptr;
        }
    }
    param->actionTriggerCtrlBuffer.freeBuffer();
    
    for (s32 i {0}; i < param->localPropertyTriggerCtrlBuffer.getSize(); ++i) {
        if (param->localPropertyTriggerCtrlBuffer[i] != nullptr) {
            delete param->localPropertyTriggerCtrlBuffer[i];
            param->localPropertyTriggerCtrlBuffer[i] = nullptr;
        }
    }
    param->localPropertyTriggerCtrlBuffer.freeBuffer();

    for (s32 i {0}; i < param->globalPropertyTriggerCtrlBuffer.getSize(); ++i) {
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
        for (s32 i {0}; i < param->actionTriggerCtrlBuffer.getSize(); ++i) {
            if (param->actionTriggerCtrlBuffer[i] != nullptr)
                param->actionTriggerCtrlBuffer[i]->reset();
        }

        for (s32 i {0}; i < param->localPropertyTriggerCtrlBuffer.getSize(); ++i) {
            if (param->localPropertyTriggerCtrlBuffer[i] != nullptr)
                param->localPropertyTriggerCtrlBuffer[i]->reset();
        }

        for (s32 i {0}; i < param->globalPropertyTriggerCtrlBuffer.getSize(); ++i) {
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

s32 TriggerCtrlMgr::getCurrentResActionIdx(s32 action_trigger_idx) const
{
    if (action_trigger_idx >= 0 && getUserInstance_()->getUser()->getActionSlotNum() > action_trigger_idx) {
        TriggerCtrlParam* param {getParam()};
        if (param != nullptr && param->actionTriggerCtrlBuffer.isBufferReady()) {
            ActionTriggerCtrl* action_trigger_ctrl {param->actionTriggerCtrlBuffer[action_trigger_idx]};
            if (param->actionTriggerCtrlBuffer[action_trigger_idx] != nullptr)
                return action_trigger_ctrl->getCurrentResActionIdx();
        }
    }
    return -1;
}

s32 TriggerCtrlMgr::getCurrentActionFrame(s32 action_idx) const 
{
    return -1;
}

const char* TriggerCtrlMgr::getCurrentActionName(s32 action_idx) const 
{
    return nullptr;
}

}  // namespace xlink2