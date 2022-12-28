#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2ResTriggerOverwriteParam.h"
#include "xlink2/xlink2TriggerType.h"

namespace xlink2 {
class TriggerLocator {
public:
    u64 getOverwriteBoneMtx() const;
    u64 getTriggerOverwriteParam() const;
    u32 getTriggerTyper() const;

    void reset();

    void setTriggerInfo(TriggerType, ResTriggerOverwriteParam*, BoneMtx);

private:
};
}  // namespace xlink2