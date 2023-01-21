#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>

#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2EventSLink.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResTriggerOverwriteParam.h"
#include "xlink2/xlink2UserInstanceSLink.h"

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
    bool calc() override;
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
    void* _0;
    void* _1;
    EventSLink* mEvent;                                   // 0x18
    UserInstanceSLink* mUserInstance;                     // 0x20
    ResAssetCallTable* mResAssetCallTable;                // 0x28
    f32 _2;                                               // 0x30
    f32 _3;                                               // 0x34
    ResTriggerOverwriteParam* mResTriggerOverwriteParam;  // 0x38
    void* _4;                                             // 0x40
    u8 _5;                                                // 0x48
    u32 _6;                                             // 0x49
    u8 _7;                                                // 0x50
    u32 _8;                                             // 0x51
    void* _9;                                             // 0x58
    void* _10;                                            // 0x60
    HandleSLink* mHandle;                                 // 0x68
    void* _11;                                            // 0x70
    u16 _12;                                              // 0x78
    u16 _13;                                              // 0x7a
    f32 mVolume;                                          // 0x7c
    f32 mDeviceVolume;                                    // 0x80
    f32 mPitch;                                           // 0x84
    f32 mLpf;                                             // 0x88
    f32 mPriority;                                        // 0x8c
    f32 mVelocityX;                                       // 0x90
    f32 mVelocityY;                                       // 0x94
    f32 mVelocityZ;                                       // 0x98
};
}  // namespace xlink2