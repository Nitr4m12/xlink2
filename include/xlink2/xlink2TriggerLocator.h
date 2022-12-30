#pragma once

#include "basis/seadTypes.h"
#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2ResTriggerOverwriteParam.h"
#include "xlink2/xlink2TriggerType.h"

namespace xlink2 {
class TriggerLocator {
    virtual ~TriggerLocator();
public:
    BoneMtx* getOverwriteBoneMtx() const;
    ResTriggerOverwriteParam* getTriggerOverwriteParam() const;
    TriggerType getTriggerType() const;

    void reset();

    void setTriggerInfo(TriggerType, ResTriggerOverwriteParam*, BoneMtx, u8);

private:
    void* _0;
    u8 _1;
    TriggerType mTriggerType;
    ResTriggerOverwriteParam* mResTriggerOverwriteParam;
    BoneMtx* mBoneMtx;
    u8 _2;
};
}  // namespace xlink2