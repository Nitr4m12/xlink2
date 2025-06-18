#include "xlink2/xlink2Event.h"
#include "prim/seadScopedLock.h"
#include "xlink2/xlink2ContainerCreator.h"

namespace xlink2 {
Event::Event()
{
    mAliveAssetExecutors.initOffset(8);
    mFadeBySystemAssetExecutors.initOffset(8);
}

Event::~Event() = default;

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

void Event::finalize() 
{
    doFinalize_();
    destroyAllContainerAndAssetExecutor_();
    _0x20 = 0;
}

void Event::doFinalize_() {}

void Event::destroyAllContainerAndAssetExecutor_() 
{
    if (mpRootContainer != nullptr)
        mpRootContainer->destroy();

    for (auto& executor : mFadeBySystemAssetExecutors.robustRange()) {
        mFadeBySystemAssetExecutors.erase(&executor);
        mpUserInstance->getUser()->getSystem()->freeAssetExecutor(&executor);
    }
}

void Event::callEventCreateCallback_() {}
void Event::callEventDestroyCallback_() {}

void Event::kill() 
{
    _0x08 = _0x08 | 0x30;
    if (mpUserInstance != nullptr) {
        System* sys {mpUserInstance->getUser()->getSystem()};
        {
            auto lock {sead::makeScopedLock(*sys->getModuleLockObj())};
            if (mpRootContainer != nullptr)
                mpRootContainer->kill();

            for (auto& executor : mFadeBySystemAssetExecutors)
                executor.kill();
        }
    }
}

void Event::killOneTimeEvent() 
{
    if (mpUserInstance != nullptr) {
        System* sys {mpUserInstance->getUser()->getSystem()};
        {
            auto lock {sead::makeScopedLock(*sys->getModuleLockObj())};
            if (mpRootContainer != nullptr)
                mpRootContainer->killOneTimeEvent();

            for (auto& executor : mFadeBySystemAssetExecutors)
                if (!executor.isLoopEvent())    
                    executor.kill();
        }
    }
}

// NON-MATCHING: Instruction in the wrong place
bool Event::createRootContainer(UserInstance* user_instance, const ResAssetCallTable& asset_ctb) 
{
    mpUserInstance = user_instance;
    mpAssetCallTable = &asset_ctb;
    mGroupId = user_instance->getDefaultGroup();

    ContainerBase* root_container {ContainerCreator::CreateContainer(this, asset_ctb)};
    if (root_container == nullptr)
        return false;

    callEventCreateCallback_();
    if (!root_container->start()) {
        root_container->destroy();
        mpRootContainer = nullptr;
        return false;
    }
    mpRootContainer = root_container;
    return true;
    
}

s32 Event::getAliveAssetNum() const
{
    int asset_num {0};
    for (auto& executor : mAliveAssetExecutors)
        if (executor.isAssetValid())
            ++asset_num; 

    return asset_num;
}

s32 Event::getFadeBySystemListAssetNum() const 
{
    int asset_num {0};
    for (auto& executor : mFadeBySystemAssetExecutors)
        if (executor.isAssetValid())
            ++asset_num;

    return asset_num;
}

void Event::fade(s32 p1) 
{
    _0x08 = _0x08 | 0x10;
    if (mpUserInstance != nullptr && mpRootContainer != nullptr) {
        System* sys = {getUserInstance()->getUser()->getSystem()};
        {
            auto lock {sead::makeScopedLock(*sys->getModuleLockObj())};
            mpRootContainer->fade(p1);    
        }
    }
}

void Event::fadeBySystem() 
{
    _0x08 = _0x08 | 0x10;
    if (mpUserInstance != nullptr && mpRootContainer != nullptr) {
        System* sys = {getUserInstance()->getUser()->getSystem()};
        {
            auto lock {sead::makeScopedLock(*sys->getModuleLockObj())};
            mpRootContainer->fadeBySystem();    
        }
    }
}

void Event::fixDelayParam_() {}

}  // namespace xlink2