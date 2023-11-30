#include <xlink2/xlink2Locator.h>

namespace xlink2 {
void Locator::reset()
{
    _0 = nullptr;
    _1 = 0;
}

void Locator::setTriggerInfo(TriggerType, ResTriggerOverwriteParam*, BoneMtx) {}

TriggerType Locator::getTriggerType() const
{
    return TriggerType::Invalid;
}

const ResTriggerOverwriteParam* Locator::getTriggerOverwriteParam() const
{
    return nullptr;
}

void* Locator::getOverwriteBoneMtx() const
{
    return _0;
}

bool Locator::isNeedRebind() const
{
    return false;
}

s32 Locator::getSearchedGuid() const
{
    return 0;
}

void Locator::updateDataLoadedCount()
{
    sDataLoadedCount += 1;
}
}  // namespace xlink2