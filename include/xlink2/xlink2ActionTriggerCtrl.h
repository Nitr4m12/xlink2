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
    ~ActionTriggerCtrl() override;

    void calc() override;

    void changeAction(char const*, int);
    void changeAction(int, int);
    void changeActionImpl(ResAction const*, int, UserResource const*);
    void changeActionImpl_old(ResAction const*, int, UserResource const*);

    void emitByTrigger(int);

    static u32 getActionTriggerType_(const ResActionTrigger&);
    int getCurrentResActionIdx();
    void notifyActive();
    void reset();
    void restartAction(char const*, int);
    u32 searchResAction(ResActionSlot const*, char const*, int*);
    void stopAction();

private:
    const ResActionSlot* mActionSlot {nullptr};
    // WARNING: These are temporary variables to denote that
    // something is occupying this space
    ResUserInfo mUserInfo {};
    s32 mUserBinPos {0};
    ResAction* mAction{nullptr};
    bool mIsActive{false};
};
static_assert(sizeof(ActionTriggerCtrl) == 0x40, "Wrong size for 'xlink2::ActionTriggerCtrl'");

}  // namespace xlink2