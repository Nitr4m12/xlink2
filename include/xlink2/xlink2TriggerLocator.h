#pragma once

#include "xlink2/xlink2.h"

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