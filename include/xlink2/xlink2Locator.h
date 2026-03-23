#pragma once

#include "xlink2/xlink2BoneMtx.h"
#include "xlink2/xlink2Resource.h"

namespace xlink2 {
class Locator {
public:
    Locator() : mpAssetCallTable(nullptr) {};
    explicit Locator(const ResAssetCallTable& asset_ctb)
        : mpAssetCallTable(&asset_ctb) {}
    ~Locator() = default;

    static u32 sDataLoadedCount;

    virtual void reset();
    virtual void setTriggerInfo(TriggerType, ResTriggerOverwriteParam*, BoneMtx);
    virtual TriggerType getTriggerType() const;
    virtual ResTriggerOverwriteParam* getTriggerOverwriteParam() const;
    virtual BoneMtx getOverwriteBoneMtx() const;

    bool isNeedRebind() const;
    s32 getSearchedGuid() const;
    static void updateDataLoadedCount();

    const ResAssetCallTable* getAssetCallTable() const { return mpAssetCallTable; }
    void setAssetCallTable(const ResAssetCallTable* asset_call_table) { mpAssetCallTable = asset_call_table; }

    bool get1() const { return _1; }
    void set1(u8 new_value) { _1 = new_value; }

protected:
    const ResAssetCallTable* mpAssetCallTable;
    u8 _1 {0};
};
static_assert(sizeof(Locator) == 0x18, "xlink2::Locator size mismatch");
}  // namespace xlink2
