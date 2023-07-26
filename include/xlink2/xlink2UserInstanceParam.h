#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2ModelAssetConnection.h"

namespace xlink2 {
struct UserInstanceParam {
    struct RandomEvent {
        s32 oldIndex;
        s32 newIndex;
    };

    u32 numModelAssetConnection;
    ModelAssetConnection* modelAssetConnections;
    u32 numRandomHistory;
    RandomEvent* randomHistory;
    bool isSetupRom;
};
}  // namespace xlink2