#pragma once

#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>

namespace xlink2 {
class AssetExecutor {
public:
    virtual ~AssetExecutor();
    virtual bool calc() = 0;
    virtual bool isAssetValid() const = 0;
    virtual void fade(s32) = 0;
    virtual void kill() = 0;

    virtual void requestReEmit(bool) = 0;
    virtual bool isRequestReEmit() const = 0;

    virtual void fadeBySystem() = 0;
    virtual bool isLoopEvent() const = 0;

    virtual void dumpDebugPrint() = 0;
    virtual void activateImpl_() = 0;
    virtual void onDestroy_() = 0;
    virtual void onResetOverwriteParam_() = 0;
    virtual void onFinalize_() = 0;
};
}  // namespace xlink2