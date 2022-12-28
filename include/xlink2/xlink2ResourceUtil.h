#pragma once

#include "xlink2/xlink2.h"

namespace xlink2 {
class ResourceUtil {
public:
    u32 getActionTriggerTyper(ResActionTrigger const&);
    u32 getResContainerParam(ResAssetCallTable const&);
    u32 getResSequenceContainerParam(ResAssetCallTable const&);
    u32 getResSwitchContainerParam(ResAssetCallTable const&);

private:
};
}  // namespace xlink2