#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>

#include "xlink2/xlink2ToolConnectionContext.h"

namespace xlink2 {
class IUser {
public:
    virtual void* getBoneWorldMtxPtr(char*) const = 0;
    virtual char* getActionSlotName(int) const;

    virtual void* getDebugDrawCamera() const;
    virtual void* getDebugDrawProjection() const;
    virtual char* getDebugUserName() const;

    virtual void* getUserInformation() const;
    virtual void getReservedAssetName(ToolConnectionContext*) const;

    virtual u32 getNumBone() const = 0;
    virtual char* getBoneName() const = 0;

    virtual u32 getNumAction(int) const;
    virtual char* getActionName(int, int) const;

    virtual void captureScreen() = 0;

    virtual f32 getSortKey() = 0;

    virtual sead::Matrix34f* getAutoInputMtxSource() = 0;

    virtual u64 getBoneWorldMtx(char const*, sead::Matrix34f*) const;
    virtual const sead::Matrix34f* getMtxCorrectingDrawBone() const;
};
}  // namespace xlink2