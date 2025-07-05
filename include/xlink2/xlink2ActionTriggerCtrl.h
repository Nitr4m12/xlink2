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

namespace xlink2 {
class ActionTriggerCtrl : TriggerCtrl {
public:
    ActionTriggerCtrl(UserInstance*, sead::Buffer<ModelTriggerConnection>*,
                      const ResActionSlot*);

    void reset();
    void calc() override;

    static TriggerType getActionTriggerType_(const ResActionTrigger&);
    void emitByTrigger_(s32 action_trigger_idx);

    void notifyActive();

    void changeAction(const char* name, s32 p2);
    ResAction* searchResAction_(const ResActionSlot* action_slot, const char* name, s32* idx) const;
    void stopAction();
    void changeActionImpl_(ResAction const*, s32, UserResource const*);
    void changeAction(s32 action_idx, s32 p2);
    
    s32 getCurrentResActionIdx() const;
    void changeActionImpl_old_(ResAction const*, s32, UserResource const*);
    void restartAction(const char*, s32);

    ~ActionTriggerCtrl() override;

    UserResource* getUserResource() const { return mUserInstance->getUser()->getUserResource(); }

    void setActionFrame(s32 frame) { mActionFrame = frame; }

    bool isActive() { return mIsActive; }

private:
    const ResActionSlot* mActionSlot {nullptr};
    u32 mNameHash;
    s32 mActionFrame;
    // ResUserInfo mUserInfo {};
    s32 mUserBinPos {0};
    ResAction* mAction{nullptr};
    bool mIsActive{false};
};
static_assert(sizeof(ActionTriggerCtrl) == 0x40, "xlink2::ActionTriggerCtrl size mismatch");

}  // namespace xlink2