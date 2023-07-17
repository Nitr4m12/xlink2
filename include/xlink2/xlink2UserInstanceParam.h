#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2ModelAssetConnection.h"

namespace xlink2 {
struct UserInstanceParam {
    u32 numModelAssetConnection;
    ModelAssetConnection* modelAssetConnections;
    u32 numRandomHistory;
    void* _18;
    bool isSetupRom;
};
}  // namespace xlink2