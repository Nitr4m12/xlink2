#pragma once

#include "basis/seadTypes.h"

namespace xlink2 {
enum class ContainerType : s32 {
    Switch,
    Random,
    Random2,
    Blend,
    Sequence,
    Asset
};

struct ResContainerParam {
    ContainerType type;
    s32 childrenStartIndex;
    s32 childrenEndIndex;
};

struct ResSequenceContainerParam : public ResContainerParam {

};

struct ResSwitchContainerParam : public ResContainerParam {
    u32 watchPropertyNamePos;
    s32 watchPropertyId;
    s16 localPropertyNameIdx;
    bool isGlobal;
};
}  // namespace xlink2