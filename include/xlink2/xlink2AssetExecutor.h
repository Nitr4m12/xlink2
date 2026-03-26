#pragma once

#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>
#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2Resource.h"
#include "xlink2/xlink2Types.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class Event;

class AssetExecutor {
public:
    AssetExecutor() = default;
    explicit AssetExecutor(Event* event) : mpEvent(event) {}

    virtual ~AssetExecutor() = default;

    virtual u32 calc() = 0;

    virtual bool isAssetValid() const = 0;

    virtual void fade(s32) = 0;
    virtual void kill() = 0;

    virtual void requestReEmit(bool) = 0;
    virtual bool isRequestReEmit() const = 0;

    virtual void fadeBySystem() = 0;

    virtual bool isLoopEvent() const = 0;

    virtual void dumpDebugPrint();

    virtual bool activateImpl_() = 0;

    virtual void onDestroy_();
    virtual void onResetOverwriteParam_() = 0;
    virtual void onFinalize_() = 0;

    Event* getEvent() { return mpEvent; }
    void setEvent(Event* event) { mpEvent = event; }

    void setUserInstance(UserInstance* new_instance) { mpUserInstance = new_instance; }

    ContainerType getContainerType() const { return mContainerType; }
    void setContainerType(ContainerType new_type) { mContainerType = new_type; }

    ResAssetCallTable* getAssetCallTable() const { return mpAssetCallTable; }
    void setAssetCallTable(ResAssetCallTable* asset_ctb) { mpAssetCallTable = asset_ctb; }

    void set34(f32 new_val) { _0x34 = new_val; }

    ResTriggerOverwriteParam* getTriggerOverwriteParam() { return mpTriggerOverwriteParam; }

    void setOverwriteParam(ResTriggerOverwriteParam* param, BoneMtx bone_mtx)
    {
        mpTriggerOverwriteParam = param;
        mBoneMtx = bone_mtx;
    }

    void resetOverwriteParam(ResTriggerOverwriteParam* param, BoneMtx bone_mtx)
    {
        mpTriggerOverwriteParam = param;
        mBoneMtx = bone_mtx;
        onResetOverwriteParam_();
    }

protected:
    void* _0x8{};
    void* _0x10{};
    Event* mpEvent{};
    UserInstance* mpUserInstance{};
    ResAssetCallTable* mpAssetCallTable{};
    ContainerType mContainerType{ContainerType::Switch};
    f32 _0x34{};
    ResTriggerOverwriteParam* mpTriggerOverwriteParam{};
    BoneMtx mBoneMtx;
};
static_assert(sizeof(AssetExecutor) == 0x50, "Wrong size for 'xlink2::AssetExecutor'");
}  // namespace xlink2