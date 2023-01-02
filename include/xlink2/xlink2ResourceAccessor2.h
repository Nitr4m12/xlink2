#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResParam.h"
#include "xlink2/xlink2ResRandomCallTable.h"
#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2UserResource.h"

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
    UserInstance* mUserInstance;
    UserResource* mUserResource;
    ResAssetCallTable* mResAssetCallTable;
    void* _0;
    u32 _1;
    u8 _2;
    void* _3;
    User* mUser;
};
}  // namespace xlink2