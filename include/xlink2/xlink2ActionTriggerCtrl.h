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
class ActionTriggerCtrl {
    virtual ~ActionTriggerCtrl();

public:
    ActionTriggerCtrl(UserInstance* param_1, sead::Buffer<ModelTriggerConnection>* param_2,
                      ResActionSlot* param_3);

    void calc();
    void changeAction(char const*, int);
    void changeAction(int, int);
    void changeActionImpl_(ResAction const*, int, UserResource const*);
    void changeActionImpl_old_(ResAction const*, int, UserResource const*);

    void emitByTrigger_(int);

    u32 getActionTrigger(ResActionTrigger const&);
    int getCurrentResActionIdx();
    void notifyActive();
    void reset();
    void restartAction(char const*, int);
    u32 searchResAction_(ResActionSlot const*, char const*, int*);
    void stopAction();

private:
    // TriggerCtrl* mTriggerCtrl {nullptr};
    UserInstance* mUserInstance;
    sead::Buffer<ModelTriggerConnection>* mBuffer;
    ResActionSlot* mResActionSlot;
    // WARNING: These are temporary variables to denote that
    // something is occupying this space
    u64 _0;
    u32 _1;
    u64 _2;
    u8 _3;
};
}  // namespace xlink2