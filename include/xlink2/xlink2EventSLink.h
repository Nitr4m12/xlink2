#pragma once

#include <container/seadPtrArray.h>

#include "xlink2/xlink2Event.h"

namespace aal {
class Handle;
}

namespace xlink2 {
class AssetExecutorSLink;
class EventSLink : Event {
public:
    ~EventSLink() override;
    void initializeImpl_() override;
    
    u64 getPos(sead::Vector3f*) const;
    u64 getVelocity() const;

    u64 getAliveAssetExecutor() const;
    u64 getAliveAssetExecutor(sead::PtrArray<AssetExecutorSLink>*) const;

    u64 getSoundHandle(sead::PtrArray<aal::Handle>*) const;



private:
    u32 _16;
    u32 _17;
    u32 _18;
    u32 _19;
    void* _20;
    u32 _21;
    u32 _22;
    u32 _23;
    sead::Vector3f mPos;
    sead::Vector3f mVelocity;
    void* _30;
    u16 _31;
};
static_assert(sizeof(EventSLink) == 0xe8, "xlink2::EventSLink size mismatch");

}  // namespace xlink2