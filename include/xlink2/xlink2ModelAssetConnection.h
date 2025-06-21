#pragma once

#include <math/seadMatrix.h>

namespace xlink2 {
class ModelAssetConnection {
public:
    virtual ~ModelAssetConnection();

    const sead::Matrix34f* mRootMtx;
    u8 _1;
};
}