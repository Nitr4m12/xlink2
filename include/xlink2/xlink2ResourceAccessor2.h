#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResParam.h"
#include "xlink2/xlink2ResRandomCallTable.h"

namespace xlink2 {
class ResourceAccessor2 {
public:
    f32 getCurveValue(ResParam const&) const;
    f32 getRandomValue(ResRandomCallTable const&) const;
    f32 getRandomValue(ResRandomCallTable const&, f32) const;
    f32 getRandomValueWeightMax(ResRandomCallTable const&, f32) const;
    f32 getRandomValueWeightMin(ResRandomCallTable const&, f32) const;
    s64 getResRandomCallTable(ResParam const&) const;

private:
    ResAssetCallTable* mResAssetCallTable;
};
}