#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>

#include "xlink2/xlink2ModelAssetConnection.h"

namespace xlink2 {
struct UserInstanceParam {
    struct RandomEvent {
        s32 oldIndex;
        s32 newIndex;
    };

    sead::Buffer<ModelAssetConnection> modelAssetConnectionBuffer;
    sead::Buffer<RandomEvent> randomEventBufffer;
    bool isSetupRom;
};
static_assert(sizeof(UserInstanceParam) == 0x28, "xlink2::UserInstanceParam size mismatch");

}  // namespace xlink2