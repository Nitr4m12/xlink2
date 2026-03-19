#pragma once

#include <container/seadPtrArray.h>

#include "xlink2/xlink2Event.h"

namespace aal {
class Handle;
}

namespace xlink2 {
class AssetExecutorSLink;
class EventSLink : public Event {
public:
    ~EventSLink() override = default;

    void initializeImpl_() override;
    
    bool getPos(sead::Vector3f*) const;
    const sead::Vector3f& getVelocity() const;

    AssetExecutorSLink* getAliveAssetExecutor() const;
    s32 getAliveAssetExecutor(sead::PtrArray<AssetExecutorSLink>*) const;

    s32 getSoundHandle(sead::PtrArray<aal::Handle>*) const;

private:
    u8 padding[3];
    u8  _0x98;
    sead::BitFlag8 _0x99;
    u16 _0x9a;
    f32 mVolumeScale;
    f32 mVolumeTvScale;
    f32 mPitchScale;
    f32 mLpfScale;
    f32 mAngle;
    f32 mPriorityScale;
    u32 mBiquadType;
    float mBiquadValue;
    sead::Vector3f mPosition;
    sead::Vector3f mVelocity;
    void* _0xd8;
    u16 _0xe0;
};
static_assert(sizeof(EventSLink) == 0xe8, "xlink2::EventSLink size mismatch");

}  // namespace xlink2