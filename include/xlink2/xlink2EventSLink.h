#pragma once

#include <container/seadPtrArray.h>
#include <math/seadVectorFwd.h>

#include "xlink2/xlink2AssetExecutorSLink.h"
#include "xlink2/xlink2Event.h"

namespace xlink2 {
class AssetExecutorSLink;
class EventSLink : Event {
    ~EventSLink() override;

public:
    void initializeImpl_() override;

    u64 getAliveAssetExecutor() const;
    u64 getAliveAssetExecutor(sead::PtrArray<AssetExecutorSLink>*) const;
    u64 getPos(sead::Vector3f*) const;
    // u64 getSourceHandle(sead::PtrArray<aal::Handle>*) const;
    u64 getVelocity() const;

private:
    u32 _16;
    u32 _17;
    u32 _18;
    u32 _19;
    void* _20;
    u32 _21;
    u32 _22;
    u32 _23;
    u32 _24;
    u32 _25;
    u32 _26;
    u32 _27;
    u32 _28;
    void* _29;
    void* _30;
    u16 _31;

    // 0xbc
    // sead::Vector3f* _24;

    // 0xc4
    // u32

    // 0xc8
    // sead::Vector3f* mVelocity
};
}  // namespace xlink2