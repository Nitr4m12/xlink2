#include <prim/seadScopedLock.h>

#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2ContainerCreator.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2System.h"

namespace xlink2 {
Event::Event()
{
    mAliveAssetExecutors.initOffset(8);
    mFadeBySystemAssetExecutors.initOffset(8);
}

void Event::initialize(u32 create_id)
{
    mBitFlag = 2;
    mpUserInstance = nullptr;
    mpAssetCallTable = nullptr;
    mTriggerType = TriggerType::Invalid;
    _0x90 = 1;
    mCreateId = create_id;
    mBoneMtx.rawMtx = nullptr;
    mpRootContainer = nullptr;
    mpTriggerOverwriteParam = nullptr;
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

    for (auto& executor : mFadeBySystemAssetExecutors.robustRange()) {
        mFadeBySystemAssetExecutors.erase(&executor);
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

    bool fade_by_system {mFadeBySystemAssetExecutors.isEmpty()};
    if (!fade_by_system) {
        for (auto& executor : mFadeBySystemAssetExecutors.robustRange()) {
            if (executor.calc()) {
                mFadeBySystemAssetExecutors.erase(&executor);
                mpUserInstance->getUser()->getSystem()->freeAssetExecutor(&executor);
            }
        }
        fade_by_system = mFadeBySystemAssetExecutors.isEmpty();
    }

    return fade_by_system && container_done;
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

void Event::setOverwriteParam(TriggerType trigger_type, ResTriggerOverwriteParam* param, BoneMtx bone_mtx)
{
    mTriggerType = trigger_type;
    mpTriggerOverwriteParam = param;
    mBoneMtx = bone_mtx;

    for (auto& executor : mAliveAssetExecutors)
        executor.resetOverwriteParam(mpTriggerOverwriteParam, mBoneMtx);

    for (auto& executor : mFadeBySystemAssetExecutors)
        executor.resetOverwriteParam(mpTriggerOverwriteParam, mBoneMtx);
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