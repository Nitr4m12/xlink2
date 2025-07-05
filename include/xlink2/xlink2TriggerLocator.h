#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2ResParam.h"
#include "xlink2/xlink2TriggerType.h"

namespace xlink2 {
class TriggerLocator : Locator {
public:
    void setTriggerInfo(TriggerType, ResTriggerOverwriteParam*, BoneMtx) override;

    void reset() override;

    TriggerType getTriggerType() const override;
    ResTriggerOverwriteParam* getTriggerOverwriteParam() const override;
    
    BoneMtx getOverwriteBoneMtx() const override;

private:
    TriggerType mTriggerType;
    ResTriggerOverwriteParam* mpResTriggerOverwriteParam;
    BoneMtx mBoneMtx;
};
}  // namespace xlink2