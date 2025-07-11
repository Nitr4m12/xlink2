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
    mEventList = {};
    mEventList.initOffset(10);
    mUser = user;
    mIUser = create_arg.iUser;
    mRootMtx = create_arg.rootMtx;
    mRootPos = create_arg.rootPos;
    mSortKey = INFINITY;
    mScale = create_arg.scale;
    mValueChangedBitfield = 0;
    mPropertyValueArray = nullptr;
    mTriggerCtrlMgr = {};
    _0x98 = nullptr;
    mBitFlag = 0;
    if (!create_arg.rootMtx.rawMtx) {
        mRootMtx.rawMtx = &sead::Matrix34f::ident;
        mRootMtx._0 = 0;
    }
    if (!create_arg.scale)
        mScale = &sead::Vector3f::ones;

    u16 prop_define_table_num = mUser->getNumLocalProp();
    if (prop_define_table_num > 0)
        mPropertyValueArray = new (heap, 8) PropertyValueType[prop_define_table_num << 2];

    mTriggerCtrlMgr.initialize(create_arg.actionSlotCount, create_arg.localPropertyCount, heap);

    mParams.fill(nullptr);
}

void UserInstance::destroy() 
{
    {
        auto lock = sead::makeScopedLock(*mUser->getSystem()->getModuleLockObj());
        for (auto& event : mEventList)
            event.fadeBySystem();

        mUser->getSystem()->freeAllEvent(&mEventList);

        onDestroy_();

        if (mParams[0] != nullptr)
            freeInstanceParam_(mParams[0], ResMode::Rom);

        if (mParams[1] != nullptr)
            freeInstanceParam_(mParams[1], ResMode::Editor);

        auto* property_value_array {mPropertyValueArray};
        if (property_value_array != nullptr) {
            delete[] property_value_array;
            mPropertyValueArray = nullptr;
        }
        
        mUser->getSystem()->removeUserInstance(this);
        
        delete this;
    }
}

bool UserInstance::checkAndErrorCallInCalc(const char* /*unused*/, ...) const 
{
    return true;
}

void UserInstance::printLogFadeOrKill(Event const* /*unused*/, char const* /*unused*/, ...) const {}

void UserInstance::preCalc() 
{
    if (mBitFlag.isOffBit(1)) {
        System* sys {mUser->getSystem()};
        if (sys != nullptr && sys->isCallEnabled())
            mTriggerCtrlMgr.calc();
    }
}

void UserInstance::doOtameshiEmit_() {}

void UserInstance::postCalc() 
{
    if (mBitFlag.isOffBit(1)) {
        System* sys {mUser->getSystem()};
        if (sys && sys->isCallEnabled()) {
            onPostCalc_();
            mValueChangedBitfield.makeAllZero();
            mBitFlag.reset(4);
        }
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

void UserInstance::linkPropertyDefinitionToValueStruct(u32 idx,
                                                       const PropertyDefinition* prop_define) 
{
    switch (prop_define->getType()) {
        case PropertyType::Enum:
        case PropertyType::S32:
            mPropertyValueArray[idx].valueInt = 0;
            break;
        case PropertyType::F32:
            mPropertyValueArray[idx].valueFloat = 0.0;
            break;
    }
}

bool UserInstance::isInstanceParamValid() const 
{
    if (mParams[mBitFlag & 1])
        return mParams[mBitFlag & 1]->isSetupRom;
    return false;
}

ModelAssetConnection* UserInstance::getModelAssetConnection(u32 idx) const 
{
    UserInstanceParam* param = mParams[mBitFlag & 1];
    if (param != nullptr && param->isSetupRom)
        return &param->modelAssetConnectionBuffer[idx];
    return nullptr;
}

void UserInstance::searchAndEmitImpl(const char* name, Handle* handle) 
{
    System* sys {mUser->getSystem()};
    if (name != nullptr && sys->isCallEnabled()) {
        if (checkAndErrorCallWithoutSetup_("searchAndEmit(%s)", name)) {
            Locator l{};
            if (mUser->getUserResource()->searchAssetCallTableByName(&l, name))
                emitImpl(l, handle);
        }
    }
}

bool UserInstance::checkAndErrorCallWithoutSetup_(const char* fmt, ...) const 
{
    if (mParams[mBitFlag & 1] != nullptr && mParams[mBitFlag & 1]->isSetupRom)
        return true;

    va_list args;
    va_start(args, fmt);
    sead::FixedSafeString<256> msg;
    msg.formatV(fmt, args);
    va_end(args);
    mUser->getSystem()->addError(Error::Type::CallWithoutSetup, mUser, "%s", msg.cstr());
    return false;
}

void UserInstance::printLogSearchAsset_(bool /*unused*/, char const* /*unused*/, ...) const {}

void UserInstance::printLogEmitFailed(char const* /*unused*/, char const* /*unused*/, ...) const {}

bool UserInstance::isDebugLogEnable(DebugLogFlag /*unused*/) const 
{
    return false;
}

void UserInstance::checkAndBreakWhenEmit_(const char* /*unused*/) {}

s32 UserInstance::getCurrentResActionIdx(s32 idx) const 
{
    return mTriggerCtrlMgr.getCurrentResActionIdx(idx);
}

bool UserInstance::searchAsset(Locator* locator, const char* name) 
{
    locator->reset();
    if (mUser->getSystem()->isCallEnabled())
        return mUser->getUserResource()->searchAssetCallTableByName(locator, name);
    return false;
}

bool UserInstance::searchAsset(Locator* locator, u32 name_hash) 
{
    locator->reset();
    if (mUser->getSystem()->isCallEnabled())
        return mUser->getUserResource()->searchAssetCallTableByHash(locator, name_hash);
    return false;
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

void UserInstance::printLogContainerSelect(const Event& /*unused*/, const char* /*unused*/, ...) const {}
void UserInstance::printLogEmitFailed(const Event& /*unused*/, char const* /*unused*/, ...) const {}

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
    if (arg.rootMtx.rawMtx == nullptr)
        mRootMtx.reset();
    else
        mRootMtx = arg.rootMtx;

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
    param->randomHistoryBuffer.freeBuffer();
}

void UserInstance::onSetupInstanceParam_(ResMode /*unused*/, sead::Heap* /*unused*/) {}
bool UserInstance::doEventActivatingCallback_(const Locator& /*unused*/) 
{
    return false;
}
void UserInstance::doEventActivatedCallback_(const Locator& /*unused*/, Event* /*unused*/) {}
}  // namespace xlink2