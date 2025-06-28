#pragma once

#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>

#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2ContainerType.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResParam.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class Event;
class UserInstance;

class AssetExecutor {
public:
    virtual ~AssetExecutor();

    virtual u32 calc() = 0;

    virtual bool isAssetValid() const = 0;

    virtual void fade(s32) = 0;
    virtual void kill() = 0;

    virtual void requestReEmit(bool) = 0;
    virtual bool isRequestReEmit() const = 0;

    virtual void fadeBySystem() = 0;

    virtual bool isLoopEvent() const = 0;

    virtual void dumpDebugPrint();

    virtual void activateImpl_() = 0;

    virtual void onDestroy_();
    virtual void onResetOverwriteParam_() = 0;
    virtual void onFinalize_() = 0;

    BoneMtx boneMtx() { return mBoneMtx; }
    void boneMtx(BoneMtx new_mtx) { mBoneMtx = new_mtx; }

    u8 _0x48() {return mBoneMtx._0; }
    void _0x48(u8 new_val) {mBoneMtx._0 = new_val; }

    ResTriggerOverwriteParam* triggerOverwriteParam() { return mpTriggerOverwriteParam; }
    void triggerOverwriteParam(ResTriggerOverwriteParam* new_param) { mpTriggerOverwriteParam = new_param; }

protected:
    u8 _0x08[0x10];
    class Event* mpEvent;
    UserInstance* mpUserInstance;
    ResAssetCallTable* mpAssetCallTable;
    ContainerType mContainerType;
    float _0x34;
    ResTriggerOverwriteParam* mpTriggerOverwriteParam;
    BoneMtx mBoneMtx;
};
static_assert(sizeof(AssetExecutor) == 0x50, "Wrong size for 'xlink2::AssetExecutor'");
}  // namespace xlink2