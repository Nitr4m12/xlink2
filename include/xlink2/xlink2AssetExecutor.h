#pragma once

#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>

namespace xlink2 {
class AssetExecutor {
    virtual ~AssetExecutor();

public:
    void dumpDebugPrint();
    void onDestroy();
};
}  // namespace xlink2