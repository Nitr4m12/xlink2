#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>

#include "xlink2/xlink2AssetExecutor.h"

namespace xlink2 {
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
    void onFinalize();
    void onResetOverwriteParam();

    void requestReEmit(bool);

    void updateParam();
    void updateParamFirst();
private:
    // offset 0x18
    // EventSLink* mEventSLink;

    // offset 0x20
    // UserInstanceSLink* mUserInstance;

    // offset 0x38
    // ResAssetCallTable* mResAssetCallTable;

    // offset 0x68
    // aal::Handle* mHandle;

};
}