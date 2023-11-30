#include "xlink2/xlink2Event.h"

namespace xlink2 {
Event::Event()
{
    mAssetExecutors.initOffset(8);
    mAssetExecutors2.initOffset(8);
}

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

void Event::initializeImpl_() {}
void Event::doFinalize_() {}
void Event::callEventCreateCallback_() {}
void Event::callEventDestroyCallback_() {}
void Event::fixDelayParam_() {}
}  // namespace xlink2