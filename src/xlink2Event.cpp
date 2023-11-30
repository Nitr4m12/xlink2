#include "xlink2/xlink2Event.h"

namespace xlink2 {
void Event::initializeImpl_() {}
void Event::doFinalize_() {}
void Event::callEventCreateCallback_() {}
void Event::callEventDestroyCallback_() {}
void Event::fixDelayParam_() {}

void Event::initialize(u32 param_int)
{
    _0x08 = 2;
    mpUserInstance = nullptr;
    mpAssetCallTable = nullptr;
    mTriggerType = TriggerType::Invalid;
    _0x90 = 1;
    _0x20 = param_int;
    mpRootContainer = nullptr;
    mpTriggerOverwriteParam = nullptr;
    mpBoneMtx = nullptr;
    this->initializeImpl_();
}
}  // namespace xlink2