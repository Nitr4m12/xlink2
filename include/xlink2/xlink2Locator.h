#pragma once

#include "xlink2/xlink2.h"

namespace xlink2 {
class Locator {
    s32 getOverwriteBoneMtx() const;
    s32 getSearchedGuid() const;
    s32 getTriggerOverwriteParam() const;
    s32 getTriggerType() const;
    bool isNeedRebind() const;

    void reset();

    TriggerType setTriggerInfo(TriggerType, ResTriggerOverwriteParam*, BoneMtx);
    void updateDataLoadedCount();
};
}