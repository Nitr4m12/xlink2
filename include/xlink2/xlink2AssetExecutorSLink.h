#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>

#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2HandleSLink.h"

namespace xlink2 {
class EventSLink;
class AssetExecutorSLink : AssetExecutor {
    ~AssetExecutorSLink() override;

public:
    void _applyParam(sead::BitFlag32);
    void _updateParam();
    void _updateParamFirst();

    void activateImpl_() override;
    void appendAalInfoStr(sead::BufferedSafeString*);
    void applyParam(bool);
    u32 calc() override;
    void* emitSound();
    void fade(s32) override;
    void fadeBySystem() override;

    f32 getPlayingTime() const;
    s32 getPriority() const;
    s32 getPriority_Spatial() const;

    bool isAssetValid() const override;
    bool isLoopEvent() const override;
    bool isRequestReEmit() const override;

    void kill() override;
    void onFinalize_() override;
    void onResetOverwriteParam_() override;

    void requestReEmit(bool) override;

    void updateParam();
    void updateParamFirst();

private:
    u8 _7;
    u32 _8;
    void* _9;
    void* _10;
    HandleSLink* mHandle;
    void* _11;
    u16 _12;
    u16 _13;
    f32 mVolume;
    f32 mDeviceVolume;
    f32 mPitch;
    f32 mLpf;
    f32 mPriority;
    f32 mVelocityX;
    f32 mVelocityY;
    f32 mVelocityZ;
    u8 p[0x8];
};
static_assert(sizeof(AssetExecutorSLink) == 0xa8, "Wrong size of 'xlink2::AssetExecutorELink'");
}  // namespace xlink2