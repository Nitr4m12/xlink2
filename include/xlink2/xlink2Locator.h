#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2ResTriggerOverwriteParam.h"
#include "xlink2/xlink2TriggerType.h"

namespace xlink2 {
class Locator {
public:
    Locator() = default;
    virtual ~Locator();

    static u32 sDataLoadedCount;

    virtual void reset();
    virtual void setTriggerInfo(TriggerType, ResTriggerOverwriteParam*, BoneMtx);
    virtual TriggerType getTriggerType() const;
    virtual const ResTriggerOverwriteParam* getTriggerOverwriteParam() const;
    virtual BoneMtx getOverwriteBoneMtx() const;


    bool isNeedRebind() const;
    s32 getSearchedGuid() const;
    void updateDataLoadedCount();

private:
    void* _0;
    u8 _1;
};
}  // namespace xlink2