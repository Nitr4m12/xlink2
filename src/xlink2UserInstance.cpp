#include <cstdarg>
#include <prim/seadScopedLock.h>

#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2ResourceAccessor.h"

namespace xlink2 {
// WIP
UserInstance::UserInstance(const CreateArg& create_arg, System* sys, User* user, sead::Heap* heap) 
{
    mEventList.clear();
    mUser = user;
    mIUser = create_arg.getIUser();
    mRootMtx._0 = create_arg.get18();
    mRootMtx.rawMtx = create_arg.getRootMtx();
    mRootPos = create_arg.getRootPos();
    mSortKey = INFINITY;
    mScale = create_arg.getScale();
    mValueChangedBitfield = 0;
    mPropertyValueArray = nullptr;
    mTriggerCtrlMgr = {};
    _0x98 = nullptr;
    mBitFlag = 0;
    mEventList.initOffset(10);
    if (!create_arg.getRootMtx()) {
        mRootMtx.rawMtx = &sead::Matrix34f::ident;
        mRootMtx._0 = 0;
    }
    if (!create_arg.getScale())
        mScale = &sead::Vector3f::ones;

    u16 prop_define_table_num = mUser->getNumLocalProp();
    if (prop_define_table_num > 0)
        mPropertyValueArray = new (heap, 8) PropertyValueType[prop_define_table_num << 2];

    mTriggerCtrlMgr.initialize(create_arg.getActionSlotCount(), create_arg.getLocalPropertyCount(), heap);

    mParams.fill(nullptr);
}

// NON-MATCHING: One instruction missing
void UserInstance::destroy() 
{
    {
        auto lock = sead::makeScopedLock(*mUser->getSystem()->getModuleLockObj());
        for (auto& event : mEventList)
            event.fadeBySystem();

        mUser->getSystem()->freeAllEvent(&mEventList);

        onDestroy_();

        if (mParams[0])
            freeInstanceParam_(mParams[0], ResMode::Rom);

        if (mParams[1])
            freeInstanceParam_(mParams[1], ResMode::Editor);

        PropertyValueType* prop_val_arr {mPropertyValueArray};
        mPropertyValueArray = nullptr;
        delete[] prop_val_arr;
        
        mUser->getSystem()->removeUserInstance(this);
        delete this;
    }
}

bool UserInstance::checkAndErrorCallInCalc(const char* /*unused*/, ...) const 
{
    return true;
}

void UserInstance::printLogFadeOrKill(Event const* /*unused*/, char const* /*unused*/, ...) const {}

// NON-MATCHING: One instruction missing
void UserInstance::preCalc() 
{
    if (mBitFlag.isOffBit(1)) {
        if (mUser->getSystem() != nullptr && mUser->getSystem()->isCallEnabled())
            mTriggerCtrlMgr.calc();
    }
}

void UserInstance::doOtameshiEmit_() {}

// NON-MATCHING: One instruction missing
void UserInstance::postCalc() 
{
    if (mBitFlag.isOffBit(1) && mUser->getSystem() && mUser->getSystem()->isCallEnabled()) {
        onPostCalc_();
        mValueChangedBitfield = 0;
        mBitFlag.reset(4);
    }
}

void UserInstance::reset() 
{
    clearAllEvent();
    mTriggerCtrlMgr.reset();
    onReset_();
}

void UserInstance::killAll() 
{
    clearAllEvent();
    mTriggerCtrlMgr.reset();
}

void UserInstance::sleep()
{
    if (mBitFlag.isOffBit(1)) {
        {
            auto lock = sead::makeScopedLock(*mUser->getSystem()->getModuleLockObj());
            for (auto& event : mEventList)
                event.fadeBySystem();

            mUser->getSystem()->freeAllEvent(&mEventList);
        }
        mBitFlag.set(2);
    }
}

void UserInstance::setIsActive(bool is_active) 
{
    if (!(is_active ^ mBitFlag.isOnBit(1))) {
        if (is_active)
            mTriggerCtrlMgr.notifyActive();
        else
            sleep();
        u8 flag_bits;
        if (!is_active)
            flag_bits = mBitFlag | 2;
        else
            flag_bits = mBitFlag & 0b11111101;
        mBitFlag = flag_bits;
    }
}

void UserInstance::killAllOneTimeEvent()
{
    {
        auto lock = sead::makeScopedLock(*mUser->getSystem()->getModuleLockObj());
        for (auto& event : mEventList)
            event.killOneTimeEvent();
    }
}

void UserInstance::clearAllEvent() 
{
    {
        auto lock = sead::makeScopedLock(*mUser->getSystem()->getModuleLockObj());
        for (auto& event : mEventList)
            event.kill();

        mUser->getSystem()->freeAllEvent(&mEventList);
    }
}

// NON-MATCHING: Needs linkPropertyDefinitionToValueStruct
void UserInstance::setupResource(sead::Heap* heap)
{
    if (mUser->getSystem()->isCallEnabled()) {
        {
            auto lock = sead::makeScopedLock(*mUser->getSystem()->getModuleLockObj());
            UserInstanceParam* param_inst {mParams[0]};
            if (param_inst == nullptr || !param_inst->isSetupRom) {
                UserResourceParam* param_res {mUser->getUserResource()->getParamBuffer()[0]};
                if (param_res == nullptr || !param_res->isSetup) {
                    mUser->getUserResource()->setup(heap);
                }
                if (mParams[0] == nullptr) {
                    mParams[0] = allocInstanceParam_(heap);
                    setupInstanceParam_(ResMode::Rom, heap);
                    mTriggerCtrlMgr.allocAndSetupCtrlParam(ResMode::Rom, heap);
                }
                mUser->getSystem()->registUserForGlobalPropertyTrigger(mUser);
            }

            UserResourceParam* param_res {mUser->getUserResource()->getParamBuffer()[1]};
            if (mUser->getUserResource()->getResMode() == ResMode::Editor && 
                mUser->getUserResource()->getParamBuffer()[1] != nullptr && 
                mUser->getUserResource()->getParamBuffer()[1]->isSetup) {
                sead::Heap* primary_heap {mUser->getSystem()->getPrimaryHeap()};
                if (mParams[1] != nullptr)
                    freeInstanceParam_(mParams[1], ResMode::Editor);

                mParams[1] = allocInstanceParam_(primary_heap);
                setupInstanceParam_(ResMode::Editor, primary_heap);
                mTriggerCtrlMgr.allocAndSetupCtrlParam(ResMode::Editor, primary_heap);
                mBitFlag.set(1);
                mTriggerCtrlMgr.setResMode(ResMode::Editor);
            }
        }

        if (mUser->getNumLocalProp() > 0) {
            for (u32 i {0}; i < mUser->getNumLocalProp(); ++i) {
                if (mUser->getPropertyDefinitionEntry(i) != nullptr)
                    linkPropertyDefinitionToValueStruct(i, mUser->getPropertyDefinitionEntry(i));
            }
        }
    }
}

bool UserInstance::isSetupRomInstanceParam_() const 
{
    if (mParams[(s32)ResMode::Rom])
        return mParams[(s32)ResMode::Rom]->isSetupRom;
    return false;
}

void UserInstance::setupEditorInstanceParam() 
{
    auto* heap = mUser->getSystem()->getPrimaryHeap();

    if (mParams[(s32)ResMode::Editor])
        freeInstanceParam_(mParams[(s32)ResMode::Editor], ResMode::Editor);

    mParams[(s32)ResMode::Editor] = allocInstanceParam_(heap);
    setupInstanceParam_(ResMode::Editor, heap);
    mTriggerCtrlMgr.allocAndSetupCtrlParam(ResMode::Editor, heap);
}

void UserInstance::changeInstanceParam(ResMode mode) 
{
    u8 bit_flag = mBitFlag;
    if (mode != ResMode::Editor)
        bit_flag &= 0xfe;
    else
        bit_flag |= 1;
    mBitFlag = bit_flag;
    mTriggerCtrlMgr.setResMode(mode);
}

// NON-MATCHING: One instruction missing
void UserInstance::linkPropertyDefinitionToValueStruct(u32 index,
                                                       const PropertyDefinition* prop_define) 
{
    if (PropertyType::S32 < prop_define->getType())
        mPropertyValueArray[index].valueFloat = 0.0;
}

bool UserInstance::isInstanceParamValid() const 
{
    if (mParams[mBitFlag & 1])
        return mParams[mBitFlag & 1]->isSetupRom;
    return false;
}

ModelAssetConnection* UserInstance::getModelAssetConnection(u32 index) const 
{
    UserInstanceParam* param = mParams[mBitFlag & 1];
    if (param != nullptr && param->isSetupRom)
        return &param->modelAssetConnectionBuffer[index];
    return nullptr;
}

// WIP
void UserInstance::searchAndEmitImpl(const char* name, Handle* handle) 
{
    if (name != nullptr && mUser->getSystem()->isCallEnabled() &&
        checkAndErrorCallWithoutSetup_("searchAndEmit(%s)", name)) {
        Locator l{};
        ResAssetCallTable* b = mUser->getUserResource()->searchAssetCallTableByName(&l, name);
        if (b)
            emitImpl(l, handle);
    }
}

// WIP
bool UserInstance::checkAndErrorCallWithoutSetup_(const char* p1, ...) const 
{
    if (mParams[mBitFlag & 1] == nullptr || !mParams[mBitFlag & 1]->isSetupRom) {
        sead::FixedSafeString<256> d{};
        std::va_list args;
        va_start(args, p1);
        d.formatV(p1, args);
        mUser->getSystem()->addError(Error::Type::CallWithoutSetup, mUser, "%s", d.cstr());
        va_end(args);
        return false;
    }
    return true;
}

void UserInstance::printLogSearchAsset_(bool /*unused*/, char const* /*unused*/, ...) const {}

void UserInstance::printLogEmitFailed(char const* /*unused*/, char const* /*unused*/, ...) const {}

bool UserInstance::isDebugLogEnable(DebugLogFlag /*unused*/) const 
{
    return false;
}

void UserInstance::checkAndBreakWhenEmit_(const char* /*unused*/) {}

u64 UserInstance::getCurrentResActionIdx(s32 index) const 
{
    return mTriggerCtrlMgr.getCurrentResActionIdx(index);
}

// NON-MATCHING: Wrong register
ResAssetCallTable* UserInstance::searchAsset(Locator* locator, const char* name) 
{
    locator->reset();
    if (mUser->getSystem()->isCallEnabled())
        return mUser->getUserResource()->searchAssetCallTableByName(locator, name);
    return nullptr;
}

// NON-MATCHING: Wrong register
ResAssetCallTable* UserInstance::searchAsset(Locator* locator, u32 name_hash) 
{
    locator->reset();
    if (mUser->getSystem()->isCallEnabled())
        return mUser->getUserResource()->searchAssetCallTableByHash(locator, name_hash);
    return nullptr;
}

void UserInstance::changeAction(char const* name, int p1, int p2) 
{
    auto* sys = mUser->getSystem();
    if (sys->isCallEnabled())
        mTriggerCtrlMgr.changeAction(name, p1, p2);
}

void UserInstance::changeAction(int p1, int p2, int p3) 
{
    auto* sys = mUser->getSystem();
    if (sys->isCallEnabled())
        mTriggerCtrlMgr.changeAction(p1, p2, p3);
}

void UserInstance::setActionFrame(s32 index, s32 p2) 
{
    if (mUser->getSystem()->isCallEnabled())
        mTriggerCtrlMgr.setActionFrame(index, p2);
}

void UserInstance::stopAction(s32 index) 
{
    if (mUser->getSystem()->isCallEnabled())
        mTriggerCtrlMgr.stopAction(index);
}

bool UserInstance::isCurrentActionNeedToObserve(s32 index) const 
{
    if (mUser->getSystem()->isCallEnabled())
        return mTriggerCtrlMgr.isCurrentActionNeedToObserve(index);

    return false;
}

bool UserInstance::isCurrentActionNeedToCalc() const 
{
    return mTriggerCtrlMgr.get1() != 0;
}

void UserInstance::setPropertyValue(u32 idx, s32 value)
{
    if (mUser->getSystem()->isCallEnabled()) {
        if (mPropertyValueArray == nullptr) {
            mUser->getSystem()->addError(Error::Type::PropertyOutOfRange, 
                                         mUser, 
                                         "There is no local property definition");
            return;
        }
         
        if (mUser->getNumLocalProp() <= idx) {
            mUser->getSystem()->addError(Error::Type::PropertyOutOfRange, 
                                mUser, 
                                "ix(=%d) is out of bound (mNumLocalProp=%d)", 
                                idx, mUser->getNumLocalProp());
            return;
        }

        if (mUser->getPropertyDefinitionEntry(idx)->getType() == PropertyType::F32) {
            mUser->getSystem()->addError(Error::Type::InvalidPropertyType, 
                                mUser, 
                                "local prop ix(=%d) is F32 type\n", 
                                idx);
            return;
        }

        if (mPropertyValueArray[idx].valueInt != value) {
            mPropertyValueArray[idx].valueInt = value;
            mValueChangedBitfield.setBit(idx);
        }
    }
}

void UserInstance::setPropertyValue(u32 idx, f32 value)
{
    if (mUser->getSystem()->isCallEnabled()) {
        if (mPropertyValueArray == nullptr) {
            mUser->getSystem()->addError(Error::Type::PropertyOutOfRange, 
                                         mUser, 
                                         "There is no local property definition");
            return;
        }
         
        if (mUser->getNumLocalProp() <= idx) {
            mUser->getSystem()->addError(Error::Type::PropertyOutOfRange, 
                                mUser, 
                                "ix(=%d) is out of bound (mNumLocalProp=%d)", 
                                idx, mUser->getNumLocalProp());
            return;
        }

        if (mUser->getPropertyDefinitionEntry(idx)->getType() != PropertyType::F32) {
            mUser->getSystem()->addError(Error::Type::InvalidPropertyType, 
                                mUser, 
                                "local prop ix(=%d) is not F32 type\n", 
                                idx);
            return;
        }

        if (mPropertyValueArray[idx].valueFloat != value) {
            mPropertyValueArray[idx].valueFloat = value;
            mValueChangedBitfield.setBit(idx);
        }
    }
}

bool UserInstance::isPropertyAssigned(u32 idx) const
{
    UserResourceParam* user_param {mUser->getUserResource()->getParam()};
    if (user_param != nullptr && user_param->isSetup)
        return user_param->bitFlag.isOnBit(idx);
    return false;
}

// NON-MATCHING: Needs linkPropertyDefinitionToValueStruct
void UserInstance::setPropertyDefinition(u32 idx, const PropertyDefinition* prop_define)
{
    mUser->setPropertyDefinition(idx, prop_define);
    linkPropertyDefinitionToValueStruct(idx, prop_define);
}

char* UserInstance::getUserName() const 
{
    return mUser->getUserName();
}

void UserInstance::setDebugLogFlag(sead::BitFlag32 /*unused*/) {}

void UserInstance::setRootPos(const sead::Vector3f* root_pos) 
{
    mRootPos = root_pos;
}

void UserInstance::printLogContainerSelect(const Event&, const char*, ...) const {}
void UserInstance::printLogEmitFailed(Event const& /*unused*/, char const* /*unused*/, ...) const {}

// NON-MATCHING: two instructions in the wrong place
const sead::SafeString* UserInstance::getContainerTypeName(const ResAssetCallTable& asset_call) const 
{
    ResourceAccessor* accessor {mUser->getUserResource()->getAccessor()};
    return accessor->getCallTableTypeName(asset_call);
}

void UserInstance::fadeOrKillOtameshi(bool kill)
{
    {
        auto lock = sead::makeScopedLock(*mUser->getSystem()->getModuleLockObj());
        for (auto& event : mEventList) {
            if (kill) {
                if (event.getBitFlag() & 1)
                    event.kill();
            }
            else {
                if (event.getBitFlag() & 1)
                    event.fade(-1);
            }
        }
    }
}

void UserInstance::rebuild(const RebuildArg& arg)
{
    if (arg.rootMtx.rawMtx == nullptr) {
        mRootMtx.rawMtx = &sead::Matrix34f::ident;
        mRootMtx._0 = 0;
    }
    else {
        mRootMtx = arg.rootMtx;
    }

    mRootPos = arg.rootPos;

    mScale = arg._18 != nullptr ? arg._18 : &sead::Vector3f::ones;

    if (mParams[0] != nullptr) {
        initModelAssetConnection_(ResMode::Rom, mUser->getSystem()->getParamDefineTable(ResMode::Rom), nullptr);
    }
    if (mParams[1] != nullptr) {
        initModelAssetConnection_(ResMode::Editor, mUser->getSystem()->getParamDefineTable(ResMode::Editor), nullptr);
    }

}

u32 UserInstance::getDefaultGroup() const 
{
    return 0;
}

void UserInstance::onReset_() {}

// WIP
void UserInstance::freeInstanceParam_(UserInstanceParam* param, ResMode mode) 
{
    param->modelAssetConnectionBuffer.freeBuffer();
    param->randomHistoryBufffer.freeBuffer();
}

void UserInstance::onSetupInstanceParam_(ResMode /*unused*/, sead::Heap* /*unused*/) {}
bool UserInstance::doEventActivatingCallback_(const Locator& /*unused*/) 
{
    return false;
}
void UserInstance::doEventActivatedCallback_(const Locator& /*unused*/, Event* /*unused*/) {}

bool UserInstance::unkCheck() 
{
    return mBitFlag.isOffBit(1) && mUser->getSystem()->isCallEnabled();
}

}  // namespace xlink2