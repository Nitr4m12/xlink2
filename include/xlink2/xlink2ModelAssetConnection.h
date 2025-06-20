#pragma once

#include <math/seadMatrix.h>

namespace xlink2 {
class ModelAssetConnection {
public:
    virtual ~ModelAssetConnection();

private:
    void* _0;
    sead::Matrix34f* mRootMtx;
};
}