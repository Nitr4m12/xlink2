#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>

#include "xlink2/xlink2Types.h"

namespace xlink2 {
struct ResourceHeader {
    u8 magic[4];
    u32 dataSize;
    u32 version;
    u32 numResParam;
    u32 numResAssetParam;
    u32 numResTriggerOverwriteParam;
    u32 triggerOverwriteParamTablePos;
    u32 localPropertyNameRefTablePos;
    u32 numLocalPropertyNameRefTable;
    u32 numLocalPropertyEnumNameRefTable;
    u32 numDirectValueTable;
    u32 numRandomTable;
    u32 numCurveTable;
    u32 numCurvePointTable;
    u32 exRegionPos;
    u32 numUser;
    u32 conditionTablePos;
    u32 nameTablePos;
};
static_assert(sizeof(ResourceHeader) == 0x48, "xlink2::ResourceHeader size mismatch");

struct EditorHeader {
    u32 version;
    u32 numResParam;
    u32 numResAssetParam;
    u32 numResTriggerOverwriteParam;
    u32 triggerOverwriteParamTablePos;
    u32 localPropertyNameRefTablePos;
    u32 numLocalPropertyNameRefTable;
    u32 numLocalPropertyEnumNameRefTable;
    u32 numDirectValueTable;
    u32 numRandomTable;
    u32 numCurveTable;
    u32 numCurvePointTable;
    u32 exDataRegionPos;
    u32 userNamePos;
    u32 userBinPos;
    u32 conditionTablePos;
    u32 nameTablePos;
};
static_assert(sizeof(EditorHeader) == 0x44, "xlink2::EditorHeader size mismatch");

struct ResParam {
    u32 rawValue;
    
    s32 getValue() const { return rawValue & 0xffffff; }
    ValueReferenceType getRefType() const { return static_cast<ValueReferenceType>(rawValue >> 0x18); }
};
static_assert(sizeof(ResParam) == 0x4, "xlink2::ResParam size mismatch");

struct ResAssetParam {
    sead::BitFlag64 mask;
    ResParam params[0];
};

struct ResTriggerOverwriteParam {
    sead::BitFlag32 mask;
    ResParam params[0];
};

struct ResUserHeader {
    u32 isSetup;
    u32 numLocalProperty;
    u32 numCallTable;
    u32 numAsset;
    u32 numRandomContainer2;
    u32 numResActionSlot;
    u32 numResAction;
    u32 numResActionTrigger;
    u32 numResProperty;
    u32 numResPropertyTrigger;
    u32 numResAlwaysTrigger;
    u32 triggerTablePos;
};
static_assert(sizeof(ResUserHeader) == 0x30, "xlink2::ResUserHeader size mismatch");

struct ResAssetCallTable {
    u32 keyNamePos;
    s16 assetId;
    sead::BitFlag16 flag;
    s32 duration;
    s32 parentIndex;
    s32 guid;
    u32 keyNameHash;
    s32 paramStartPos;
    s32 conditionPos;
};
static_assert(sizeof(ResAssetCallTable) == 0x20, "xlink2::ResAssetCallTable size mismatch");

struct ResActionSlot {
    u32 namePos;
    s16 actionStartIdx;
    s16 actionEndIdx;
};
static_assert(sizeof(ResActionSlot) == 0x8, "xlink2::ResActionSlot size mismatch");

struct ResAction {
    u32 namePos;
    s32 triggerStartIdx;
    s32 triggerEndIdx;
};
static_assert(sizeof(ResAction) == 0xC, "xlink2::ResAction size mismatch");

struct ResActionTrigger {
    s32 guId;
    u32 assetCtbPos;
    s32 startFrame;
    s32 endFrame;
    sead::BitFlag16 flag;
    s16 overwriteHash;
    s32 overwriteParamPos;
};
static_assert(sizeof(ResActionTrigger) == 0x18, "xlink2::ResActionTrigger size mismatch");

struct ResProperty {
    u32 watchPropertyNamePos;
    s32 isGlobal;
    s32 triggerStartIdx;
    s32 triggerEndIdx;
};
static_assert(sizeof(ResProperty) == 0x10, "xlink2::ResProperty size mismatch");

struct ResPropertyTrigger {
    s32 guId;
    s32 assetCtbPos;
    s32 condition;
    sead::BitFlag16 flag;
    s16 overwriteHash;
    s32 overwriteParamPos;
};
static_assert(sizeof(ResPropertyTrigger) == 0x14, "xlink2::ResPropertyTrigger size mismatch");

struct ResAlwaysTrigger {
    s32 guId;
    s32 assetCtbPos;
    u16 flag;
    s16 overwriteHash;
    s32 overwriteParamPos;
};
static_assert(sizeof(ResAlwaysTrigger) == 0x10, "xlink2::ResAlwaysTrigger size mismatch");

struct ResCurveCallTable {
    u16 curvePointStartPos;
    u16 numPoint;
    u16 curveType;
    u16 isPropGlobal;
    u32 propName;
    s32 propIdx;
    s16 localPropertyNameIdx;
};
static_assert(sizeof(ResCurveCallTable) == 0x14, "xlink2::ResCurveCallTable size mismatch");

struct ResParamDefine {
    u32 namePos;
    ParamValueType type;
    union {
        s32 defaultValueInt;
        f32 defaultValueFloat;
        u32 defaultValueString;
    };
};
static_assert(sizeof(ResParamDefine) == 0xC, "xlink2::ResParamDefine size mismatch");

struct ResRandomCallTable {
    f32 minValue;
    f32 maxValue;
};
static_assert(sizeof(ResRandomCallTable) == 8, "xlink2::ResRandomCallTable size mismatch");

struct ResContainerParam {
    ContainerType type;
    s32 childrenStartIndex;
    s32 childrenEndIndex;
};
static_assert(sizeof(ResContainerParam) == 0xC, "xlink2::ResContainerParam size mismatch");

struct ResSequenceContainerParam : public ResContainerParam {};
static_assert(sizeof(ResSequenceContainerParam) == 0xC, "xlink2::ResSequenceContainerParam size mismatch");

struct ResSwitchContainerParam : public ResContainerParam {
    u32 watchPropertyNamePos;
    s32 watchPropertyId;
    s16 localPropertyNameIdx;
    bool isGlobal;
};
static_assert(sizeof(ResSwitchContainerParam) == 0x18, "xlink2::ResSwitchContainerParam size mismatch");

struct ResCondition {
    ContainerType parentContainerType;
};
static_assert(sizeof(ResCondition) == 0x4, "xlink2::ResCondition size mismatch");

struct ResSwitchCondition : public ResCondition {
    PropertyType propertyType;
    CompareType compareType;
    s32 value;
    s16 localPropertyEnumNameIdx;
    bool isSolved;
    bool isGlobal;
};
static_assert(sizeof(ResSwitchCondition) == 0x14, "xlink2::ResSwitchCondition size mismatch");

struct ResRandomCondition : public ResCondition {
    f32 weight;
};
static_assert(sizeof(ResRandomCondition) == 0x8, "xlink2::ResRandomCondition size mismatch");

struct ResEset {};

}  // namespace xlink2