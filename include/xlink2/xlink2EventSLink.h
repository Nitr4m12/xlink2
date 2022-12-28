#pragma once

#include <container/seadPtrArray.h>
#include <math/seadVectorFwd.h>

#include "xlink2/xlink2AssetExecutorSLink.h"

namespace xlink2 {
class EventSLink {
    virtual ~EventSLink();
public:
    void initializeImpl();

    u64 getAliveAssetExecutor() const;
    u64 getAliveAssetExecutor(sead::PtrArray<AssetExecutorSLink>*) const;
    u64 getPos(sead::Vector3f*) const;
    // u64 getSourceHandle(sead::PtrArray<aal::Handle>*) const;
    EventSLink* getVelocity() const;
private:
};
}