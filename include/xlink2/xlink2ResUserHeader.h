#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {
struct ResUserHeader {
    u32 isSetup;
    u32 numLocalProperty;
    s32 numCallTable;
    u32 numAsset;
    u32 numRandomContainer2;
    u32 numResActionSlot;
    u32 numResAction;
    s32 numResActionTrigger;
    u32 numResProperty;
    s32 numResPropertyTrigger;
    u32 numResAlwaysTrigger;
    u32 triggerTablePos;
};
static_assert(sizeof(ResUserHeader) == 0x30, "Wrong size for 'xlink2::ResUserHeader'");

}  // namespace xlink2