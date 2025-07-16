#pragma once

#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2Resource.h"

namespace xlink2 {
class Locator {
public:
    Locator() : mpAssetCallTable{nullptr}, _1{0} {};
    ~Locator() = default;

    static u32 sDataLoadedCount;

    virtual void reset();
    virtual void setTriggerInfo(TriggerType, ResTriggerOverwriteParam*, BoneMtx);
    virtual TriggerType getTriggerType() const;
    virtual const ResTriggerOverwriteParam* getTriggerOverwriteParam() const;
    virtual BoneMtx getOverwriteBoneMtx() const;

    bool isNeedRebind() const;
    s32 getSearchedGuid() const;
    static void updateDataLoadedCount();

    void setAssetCallTable(const ResAssetCallTable* asset_call_table) {mpAssetCallTable = asset_call_table; }

protected:
    const ResAssetCallTable* mpAssetCallTable;
    u8 _1;
};
static_assert(sizeof(Locator) == 0x18, "xlink2::Locator size mismatch");
}  // namespace xlink2
