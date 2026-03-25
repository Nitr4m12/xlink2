#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {
enum class ClipType {
    ClipKill = 1,
    ClipNone,
};

enum class CompareType : s32 {
    NotEqual,
    LessThanOrEqual,
    LessThan,
    GreaterThanOrEqual,
    GreaterThan,
    Equal,
};

enum class ContainerType : u32 {
    Switch,
    Random,
    Random2,
    Blend,
    Sequence,
    Asset
};

enum class MtxSetType {
    Programmer,
};

enum class ParamValueType : u32 {
    UInt32 = 0,
    Float = 1,
    Bool = 2,
    Enum = 3,
    String = 4,
    Arrange = 5,
    Invalid = 0xFFFFFFFF
};

enum class PropertyType : u32 {
    Enum,
    S32,
    F32,
};

enum class TriggerType : s32 {
    Action = 0,
    Property = 1,
    Always = 2,
    None = 3,
    Invalid = -1
};

enum class ValueReferenceType {
    Direct,                           
    String,                           
    Curve,                            
    Random,                           
    ArrangeGroup,                      
    Bitflag,
    Random2Pow,
    Random3Pow,
    Random4Pow,
    Random1Point5Pow,
    Random2PowWeightMin,
    Random3PowWeightMin,
    Random4PowWeightMin,
    Random1Point5PowWeightMin,
    Random2PowWeightMax,
    Random3PowWeightMax,
    Random4PowWeightMax,
    Random1Point5PowWeightMax,
};

struct PropertyValueType {
    union {
        f32 valueFloat;
        s32 valueInt;
    };
};
}