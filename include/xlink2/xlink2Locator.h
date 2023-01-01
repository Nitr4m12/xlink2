#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2ResTriggerOverwriteParam.h"
#include "xlink2/xlink2TriggerType.h"

namespace xlink2 {
class Locator {
public:
    s32 getOverwriteBoneMtx() const;
    s32 getSearchedGuid() const;
    s32 getTriggerOverwriteParam() const;
    s32 getTriggerType() const;
    bool isNeedRebind() const;

    void reset();

    TriggerType setTriggerInfo(TriggerType, ResTriggerOverwriteParam*, BoneMtx);
    void updateDataLoadedCount();
private:

};
}  // namespace xlink2