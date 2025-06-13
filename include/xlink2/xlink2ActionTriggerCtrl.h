#pragma once

#include <container/seadBuffer.h>

#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2ResAction.h"
#include "xlink2/xlink2ResActionSlot.h"
#include "xlink2/xlink2ResActionTrigger.h"
#include "xlink2/xlink2TriggerCtrl.h"
#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2UserResource.h"
#include "xlink2/xlink2ResUserInfo.h"
#include "xlink2/xlink2UserResourceParam.h"

namespace xlink2 {
class ActionTriggerCtrl : TriggerCtrl {
public:
    ActionTriggerCtrl(UserInstance*, sead::Buffer<ModelTriggerConnection>*,
                      const ResActionSlot*);

    void reset();
    void calc() override;

    static TriggerType getActionTriggerType_(const ResActionTrigger&);
    void emitByTrigger_(s32);

    void notifyActive();
    void changeAction(const char*, s32);
    u32 searchResAction_(ResActionSlot const*, char const*, s32*);
    void stopAction();
    void changeActionImpl_(ResAction const*, s32, UserResource const*);
    void changeAction(s32 action_idx, s32 p2);
    
    s32 getCurrentResActionIdx();
    void changeActionImpl_old_(ResAction const*, s32, UserResource const*);
    void restartAction(char const*, int);

    ~ActionTriggerCtrl() override;

    UserResource* getUserResource() { return mUserInstance->getUser()->getUserResource(); }
    UserResourceParam* getUserResourceParam() { return getUserResource()->getParams()[(s32)getUserResource()->getResMode()]; }

private:
    const ResActionSlot* mActionSlot {nullptr};
    ResUserInfo mUserInfo {};
    s32 mUserBinPos {0};
    ResAction* mAction{nullptr};
    bool mIsActive{false};
};
static_assert(sizeof(ActionTriggerCtrl) == 0x40, "Wrong size for 'xlink2::ActionTriggerCtrl'");

}  // namespace xlink2