#pragma once

#include "xlink2/xlink2Locator.h"

namespace xlink2 {
class TriggerLocator : public Locator {
public:
    void setTriggerInfo(TriggerType, ResTriggerOverwriteParam*, BoneMtx) override;

    void reset() override;

    TriggerType getTriggerType() const override;
    ResTriggerOverwriteParam* getTriggerOverwriteParam() const override;
    
    BoneMtx getOverwriteBoneMtx() const override;

    void setTriggerType(TriggerType type) { mTriggerType = type; }
    void setTriggerOverwriteParam(ResTriggerOverwriteParam* param) { mpResTriggerOverwriteParam = param; }
    void setBoneMtx(BoneMtx& bone_mtx) { mOverwriteBoneMtx = bone_mtx; }

private:
    TriggerType mTriggerType;
    ResTriggerOverwriteParam* mpResTriggerOverwriteParam;
    BoneMtx mOverwriteBoneMtx;
};
}  // namespace xlink2