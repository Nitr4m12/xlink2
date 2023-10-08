#pragma once

#include <container/seadBuffer.h>

#include "xlink2/xlink2ModelTriggerConnection.h"
#include "xlink2/xlink2ResAction.h"
#include "xlink2/xlink2ResActionSlot.h"
#include "xlink2/xlink2ResActionTrigger.h"
#include "xlink2/xlink2TriggerCtrl.h"
#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2UserResource.h"

namespace xlink2 {
class ActionTriggerCtrl : TriggerCtrl {
public:
    ActionTriggerCtrl(UserInstance* param_1, sead::Buffer<ModelTriggerConnection>* param_2,
                      ResActionSlot const* param_3);

    void calc() override;
    ~ActionTriggerCtrl() override;

    void changeAction(char const*, int);
    void changeAction(int, int);
    void changeActionImpl(ResAction const*, int, UserResource const*);
    void changeActionImpl_old(ResAction const*, int, UserResource const*);

    void emitByTrigger(int);

    static u32 getActionTriggerType_(ResActionTrigger const& action_trigger);
    int getCurrentResActionIdx();
    void notifyActive();
    void reset();
    void restartAction(char const*, int);
    u32 searchResAction(ResActionSlot const*, char const*, int*);
    void stopAction();

private:
    ResActionSlot const* mResActionSlot;
    // WARNING: These are temporary variables to denote that
    // something is occupying this space
    void* _0;
    u32 _1;
    ResAction* mResAction;
    u8 _2;
};
static_assert(sizeof(ActionTriggerCtrl) == 0x40, "Wrong size for 'xlink2::ActionTriggerCtrl'");

}  // namespace xlink2