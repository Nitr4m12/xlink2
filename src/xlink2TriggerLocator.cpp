#include "xlink2/xlink2TriggerLocator.h"

namespace xlink2 {
ResTriggerOverwriteParam* TriggerLocator::getTriggerOverwriteParam() const
{
    return mResTriggerOverwriteParam;
}

TriggerType TriggerLocator::getTriggerType() const
{
    return mTriggerType;
}

BoneMtx* TriggerLocator::getOverwriteBoneMtx() const
{
    return mBoneMtx;
}

void TriggerLocator::reset()
{
    _0 = nullptr;
    _1 = 0;
    mTriggerType = (TriggerType)-1;
    mResTriggerOverwriteParam = nullptr;
    mBoneMtx = nullptr;
}

void TriggerLocator::setTriggerInfo(TriggerType trigger_type, ResTriggerOverwriteParam* trigger_overwrite_param, BoneMtx bone_mtx, u8 v1)
{
    mTriggerType = trigger_type;
    mResTriggerOverwriteParam = trigger_overwrite_param;
    mBoneMtx = &bone_mtx;
    _2 = v1;
}
}