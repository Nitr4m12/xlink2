#include "xlink2/xlink2Event.h"
#include "prim/seadScopedLock.h"
#include "xlink2/xlink2ContainerCreator.h"

namespace xlink2 {
Event::Event()
{
    mAliveAssetExecutors.initOffset(8);
    mFadeBySystemList.initOffset(8);
}

Event::~Event() = default;

void Event::initialize(u32 create_id)
{
    mBitFlag = 2;
    mpUserInstance = nullptr;
    mpAssetCallTable = nullptr;
    mTriggerType = TriggerType::Invalid;
    _0x90 = 1;
    mCreateId = create_id;
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
    mCreateId = 0;
}

void Event::doFinalize_() {}

void Event::destroyAllContainerAndAssetExecutor_() 
{
    if (mpRootContainer != nullptr)
        mpRootContainer->destroy();

    for (auto& executor : mFadeBySystemList.robustRange()) {
        mFadeBySystemList.erase(&executor);
        mpUserInstance->getUser()->getSystem()->freeAssetExecutor(&executor);
    }
}

void Event::callEventCreateCallback_() {}
void Event::callEventDestroyCallback_() {}

void Event::reEmit(const ResAssetCallTable* asset_ctb) 
{
    mBitFlag.set(0b110100);
    kill();
    mBitFlag.reset(0b110100);

    destroyAllContainerAndAssetExecutor_();
    createRootContainer(mpUserInstance, *asset_ctb);
}   

void Event::kill() 
{
    mBitFlag.set(0b110000);
    if (mpUserInstance != nullptr) {
        System* sys {mpUserInstance->getUser()->getSystem()};
        {
            auto lock {sead::makeScopedLock(*sys->getModuleLockObj())};
            if (mpRootContainer != nullptr)
                mpRootContainer->kill();

            for (auto& executor : mFadeBySystemList)
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

            for (auto& executor : mFadeBySystemList)
                if (!executor.isLoopEvent())    
                    executor.kill();
        }
    }
}

bool Event::createRootContainer(UserInstance* user_instance, const ResAssetCallTable& asset_ctb) 
{
    mpUserInstance = user_instance;
    mpAssetCallTable = &asset_ctb;
    mGroupId = user_instance->getDefaultGroup();

    ContainerBase* root_container {ContainerCreator::CreateContainer(this, asset_ctb)};
    if (root_container == nullptr)
        return false;

    callEventCreateCallback_();
    if (root_container->start()) {
        mpRootContainer = root_container;
        return true;
    }
    root_container->destroy();
    mpRootContainer = nullptr;
    return false;
}

// WIP
bool Event::calc()
{

    if (mBitFlag.isOnBit(6)) {
        if (mBitFlag.isOffBit(4))
            reEmit(mpAssetCallTable);

        mBitFlag.resetBit(6);
    }  

    fixDelayParam_();

    bool container_done {true};    
    if (mpRootContainer != nullptr) {
        container_done = mpRootContainer->calc();
        if (container_done) {
            auto* container {mpRootContainer};
            mpRootContainer = nullptr;
            container->destroy();
        }
    }

    bool is_empty {mFadeBySystemList.isEmpty()};
    if (!is_empty) {
        for (auto& executor : mFadeBySystemList.robustRange()) {
            if (executor.calc()) {
                mFadeBySystemList.erase(&executor);
                mpUserInstance->getUser()->getSystem()->freeAssetExecutor(&executor);
            }
        }
        is_empty = mFadeBySystemList.isEmpty();
    }

    return is_empty && container_done;
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
    for (auto& executor : mFadeBySystemList)
        if (executor.isAssetValid())
            ++asset_num;

    return asset_num;
}

void Event::fade(s32 param_int) 
{
    mBitFlag.setBit(4);
    if (mpUserInstance != nullptr && mpRootContainer != nullptr) {
        System* sys = {mpUserInstance->getUser()->getSystem()};
        {
            auto lock {sead::makeScopedLock(*sys->getModuleLockObj())};
            mpRootContainer->fade(param_int);    
        }
    }
}

void Event::fadeBySystem() 
{
    mBitFlag.setBit(4);
    if (mpUserInstance != nullptr && mpRootContainer != nullptr) {
        System* sys = {mpUserInstance->getUser()->getSystem()};
        {
            auto lock {sead::makeScopedLock(*sys->getModuleLockObj())};
            mpRootContainer->fadeBySystem();    
        }
    }
}

void Event::fixDelayParam_() {}

}  // namespace xlink2