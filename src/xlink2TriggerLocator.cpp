#include "xlink2/xlink2TriggerLocator.h"

namespace xlink2 {
// NON-MATCHING
void TriggerLocator::setTriggerInfo(TriggerType trigger_type, ResTriggerOverwriteParam* trigger_overwrite_param, BoneMtx bone_mtx) 
{
    mTriggerType = trigger_type;
    mpResTriggerOverwriteParam = trigger_overwrite_param;
    mBoneMtx = {bone_mtx};
}

void TriggerLocator::reset() 
{
    mpAssetCallTable = nullptr;
    _1 = 0;
    mTriggerType = TriggerType::Invalid;
    mpResTriggerOverwriteParam = nullptr;
    mBoneMtx.rawMtx = nullptr;
}

TriggerType TriggerLocator::getTriggerType() const 
{
    return mTriggerType;
}

ResTriggerOverwriteParam* TriggerLocator::getTriggerOverwriteParam() const 
{
    return mpResTriggerOverwriteParam;
}

// NON-MATCHING
BoneMtx TriggerLocator::getOverwriteBoneMtx() const 
{
    return mBoneMtx;
}


}  // namespace xlink2