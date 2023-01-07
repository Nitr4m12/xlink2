#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>

#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2EventSLink.h"
#include "xlink2/xlink2UserInstanceSLink.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResTriggerOverwriteParam.h"

namespace xlink2 {
class EventSLink;
class AssetExecutorSLink : AssetExecutor {
     ~AssetExecutorSLink() override;
public:
    void _applyParam(sead::BitFlag32);
    void _updateParam();
    void _updateParamFirst();

    void activateImpl();
    void appendAalInfoStr(sead::BufferedSafeString*);
    void applyParam(bool);
    bool calc();
    void* emitSound();
    void fade(int);
    void fadeBySystem();

    f32 getPlayingTime() const;
    s32 getPriority() const;
    s32 getPriority_Spatial() const;

    void isAssetValid() const;
    void* isLoopEvent() const;
    u8 isRequestReEmit() const;

    void kill();
    void onFinalize_();
    void onResetOverwriteParam();

    void requestReEmit(bool);

    void updateParam();
    void updateParamFirst();
private:
    u64 _0;
    u64 _1;
    EventSLink* mEvent; // 0x18
    UserInstanceSLink* mUserInstance; // 0x20
    ResAssetCallTable* mResAssetCallTable; // 0x28
    f32 _2; // 0x30
    f32 _3; // 0x34
    ResTriggerOverwriteParam* mResTriggerOverwriteParam; // 0x38
    void*  _4; // 0x40
    u8 _5; //0x48
    u8 _6[7]; // 0x49
    u8 _7; // 0x50
    u8 _8[7]; // 0x51
    void* _9; // 0x58
    void* _10; // 0x60
    HandleSLink* mHandle; // 0x68
    void* _11; // 0x70
    u16 _12; // 0x78
    u16 _13; // 0x7a
    f32 mVolume; // 0x7c
    f32 mDeviceVolume; // 0x80
    f32 mPitch; // 0x84
    f32 mLpf; // 0x88
    f32 mPriority; // 0x8c
    f32 mVelocityX; // 0x90
    f32 mVelocityY; // 0x94
    f32 mVelocityZ; // 0x98

};
}