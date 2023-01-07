#pragma once

#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>

namespace xlink2 {
class AssetExecutor {
public:
    virtual ~AssetExecutor();
    virtual void dumpDebugPrint();
    virtual void onDestroy_();
};
}  // namespace xlink2