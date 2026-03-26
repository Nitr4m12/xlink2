#pragma once

#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2HandleSLink.h"
#include "xlink2/xlink2UserInstanceSLink.h"

namespace xlink2 {
class HandleSLink;

class AssetExecutorSLink : public AssetExecutor {
public:
    ~AssetExecutorSLink() override;

    u32 calc() override;
    void* emitSound();
    
    void _updateParam_();
    void updateParam_();

    bool isLoopEvent() const override;

    void fade(s32) override;
    void kill() override;
    void fadeBySystem() override;

    s32 getPriority() const;
    s32 getPriority_Spatial() const;

    f32 getPlayingTime() const;

    bool activateImpl_() override;
    
    void _updateParamFirst();
    void updateParamFirst();

    void _applyParam_(sead::BitFlag32);
    void applyParam_(bool);

    void onResetOverwriteParam_() override;

    void appendAalInfoStr(sead::BufferedSafeString*);

    bool isAssetValid() const override;

    void requestReEmit(bool) override;
    bool isRequestReEmit() const override;

    void onFinalize_() override;

    UserInstanceSLink* getUserInstance() { return static_cast<UserInstanceSLink*>(mpUserInstance); }

private:
    sead::BitFlag8 mBitFlag;
    u32 _8;
    void* _9;
    void* _10;
    HandleSLink mHandle;
    sead::BitFlag16 mParamFlag;
    u16 _13;
    f32 mVolume;
    f32 mVolumeTv;
    f32 mPitch;
    f32 mLpf;
    f32 mPriority;
    f32 mVelocityX;
    f32 mVelocityY;
    f32 mVelocityZ;
    u8 p[0x8];
};
static_assert(sizeof(AssetExecutorSLink) == 0xa8, "xlink2::AssetExecutorELink size mismatch");
}  // namespace xlink2