#pragma once

#include "basis/seadTypes.h"
#include "math/seadMatrix.h"
#include "xlink2/xlink2ToolConnectionContext.h"

namespace xlink2 {
class IUser {
public:
    u32 getActionName(int, int) const;
    u64 getActionSlotName(int) const;
    u64 getBoneWorldMtx(char const*, sead::Matrix34f*) const;
    u64 getDebugDrawCamera() const;
    u64 getDebugDrawProjection() const;
    u64 getDebugUserName() const;
    u64 getMtxCorrectingDrawBone() const;
    u64 getNumAction(int) const;
    void getReservedAssetName(ToolConnectionContext*) const;
    u64 getUserInformation();

private:
};
}