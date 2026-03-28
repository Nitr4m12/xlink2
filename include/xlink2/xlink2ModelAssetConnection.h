#pragma once

#include <math/seadMatrix.h>

#include "xlink2/xlink2BoneMtx.h"

namespace xlink2 {
class ModelAssetConnection {
public:
    virtual ~ModelAssetConnection() = default;

    BoneMtx mRootMtx {nullptr, 1};
};
}