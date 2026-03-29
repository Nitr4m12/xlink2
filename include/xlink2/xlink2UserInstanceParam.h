#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>

#include "xlink2/xlink2ModelAssetConnection.h"

namespace aal {
class Emitter;
}

namespace xlink2 {
struct UserInstanceParam {
    struct RandomHistory {
        u32 assetKeyNamePos1 {0};
        u32 assetKeyNamePos2 {0};
    };

    sead::Buffer<ModelAssetConnection> modelAssetConnectionBuffer;
    sead::Buffer<RandomHistory> randomHistoryBuffer;
    bool isSetupRom {false};
};
static_assert(sizeof(UserInstanceParam) == 0x28, "xlink2::UserInstanceParam size mismatch");

struct UserInstanceParamELink : UserInstanceParam {};
static_assert(sizeof(UserInstanceParamELink) == 0x28, "xlink2::UserInstanceParamELink size mismatch");

struct UserInstanceParamSLink : UserInstanceParam {
    sead::Buffer<aal::Emitter> emitterBuffer1;
    sead::Buffer<aal::Emitter> emitterBuffer2;
};
static_assert(sizeof(UserInstanceParamSLink) == 0x48, "xlink2::UserInstanceParamSLink size mismatch");

}  // namespace xlink2