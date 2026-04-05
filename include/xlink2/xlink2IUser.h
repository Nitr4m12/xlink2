#pragma once

#include <math/seadMatrix.h>

#include "xlink2/xlink2ToolConnectionContext.h"

namespace xlink2 {
class IUser {
public:
    virtual sead::Matrix34f* getBoneWorldMtxPtr(const char*) const = 0;
    virtual const char* getActionSlotName([[maybe_unused]] s32 action_slot_idx) const;

    virtual void* getDebugDrawCamera() const;
    virtual void* getDebugDrawProjection() const;
    virtual char* getDebugUserName() const;

    virtual const char* getUserInformation() const;
    virtual void getReservedAssetName([[maybe_unused]] ToolConnectionContext* ctx) const;

    virtual u32 getNumBone() const = 0;
    virtual const char* getBoneName(s32 bone_idx) const = 0;

    virtual u32 getNumAction([[maybe_unused]] s32) const;
    virtual char* getActionName([[maybe_unused]] s32, [[maybe_unused]] s32) const;

    virtual void captureScreen(const char*) = 0;

    virtual f32 getSortKey(const sead::Vector3f&) const = 0;

    virtual sead::Matrix34f* getAutoInputMtxSource() const = 0;

    void getBoneWorldMtx(const char*, sead::Matrix34f*) const;
    virtual sead::Matrix34f getMtxCorrectingDrawBone() const;
};
}  // namespace xlink2