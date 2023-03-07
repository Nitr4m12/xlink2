#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {
struct ResUserHeader {
    u32 isSetup;
    u32 numLocalProperty;
    u32 numCallTable;
    u32 numAsset;
    u32 numRandomContainer2;
    u32 numResActionSlot;
    u32 numResAction;
    s32 numResActionTrigger;
    u32 numResProperty;
    u32 numResPropertyTrigger;
    u32 numResAlwaysTrigger;
    u32 triggerTablePos;
    u32 userParamTablePos;
};
}  // namespace xlink2