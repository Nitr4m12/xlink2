#include <cstdarg>
#include <prim/seadScopedLock.h>

#include "xlink2/xlink2EnumPropertyDefinition.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2Handle.h"
#include "xlink2/xlink2IUser.h"
#include "xlink2/xlink2PropertyDefinition.h"
#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2UserResource.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
UserInstance::UserInstance(const CreateArg& create_arg, [[maybe_unused]] System* sys, User* user, sead::Heap* heap)
    : mUser(user), mIUser(create_arg.iUser), 
      mRootMtx(create_arg.rootMtx), mRootPos(create_arg.rootPos), 
      mScale(create_arg.scale)
{
    mEventList.initOffset(16);
    if (create_arg.rootMtx.rawMtx == nullptr) {
        mRootMtx.rawMtx = &sead::Matrix34f::ident;
        mRootMtx._0 = 0;
    }
    if (create_arg.scale == nullptr)
        mScale = &sead::Vector3f::ones;

    u16 num_local_property = mUser->getNumLocalProp();
    if (num_local_property > 0)
        mPropertyValueArray = new (heap) PropertyValueType[num_local_property];

    mTriggerCtrlMgr.initialize(create_arg.numActionSlot, create_arg.numLocalProperty, heap);

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

bool UserInstance::checkAndErrorCallInCalc([[maybe_unused]] const char* fmt, ...) const 
{
    return true;
}

void UserInstance::printLogFadeOrKill([[maybe_unused]] const Event* event, [[maybe_unused]] const char* fmt, ...) const {}

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
                if (mUser->getPropertyDefinition(i) != nullptr)
                    linkPropertyDefinitionToValueStruct(i, mUser->getPropertyDefinition(i));
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

void UserInstance::setupInstanceParam_(ResMode res_mode, sead::Heap* heap)
{
    UserInstanceParam* instance_param {getParam(res_mode)};
    UserResourceParam* resource_param {mUser->getUserResource()->getParam(res_mode)};
    ResUserHeader* user_header {resource_param->userBinParam.pResUserHeader};

    instance_param->modelAssetConnectionBuffer.allocBufferAssert(user_header->numAsset, heap);
    instance_param->randomHistoryBuffer.allocBufferAssert(user_header->numRandomContainer2, heap);

    onSetupInstanceParam_(res_mode, heap);
    instance_param->isSetupRom = true;
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

void UserInstance::printLogSearchAsset_(bool /*unused*/, const char* /*unused*/, ...) const {}

void UserInstance::emitImpl(const Locator& locator, Handle* handle)
{
    if (mUser->getSystem()->isCallEnabled() && mBitFlag.isOffBit(3)) {
        const char* asset_key_name;
        if (locator.getAssetCallTable() == nullptr)
            asset_key_name = "";
        else
            asset_key_name = solveOffset<char>(locator.getAssetCallTable()->keyNamePos);

        if (checkAndErrorCallWithoutSetup_("emit %s", asset_key_name) && mBitFlag.isOffBit(1) && 
            locator.getAssetCallTable() != nullptr && !doEventActivatingCallback_(locator)) {
            Event* event {};
            {
                auto lock {sead::makeScopedLock(*mUser->getSystem()->getModuleLockObj())};
                event = mUser->getSystem()->allocEvent();
                if (event == nullptr) {
                    mUser->getSystem()->addError(Error::Type::EventPoolFull, mUser, "emit[%s] failed.", solveOffset<char*>(locator.getAssetCallTable()->keyNamePos));
                }
                else {
                    auto* asset_call_table {locator.getAssetCallTable()};
                    if (locator.get1())
                        event->setFlagBit(0);
                    
                    auto trigger_type {locator.getTriggerType()};
                    auto* trigger_overwrite_param {locator.getTriggerOverwriteParam()};

                    event->setOverwriteParam(trigger_type, trigger_overwrite_param, locator.getOverwriteBoneMtx());

                    if (event->createRootContainer(this, *asset_call_table)) {
                        mEventList.pushBack(event);
                        if (handle != nullptr) {
                            handle->setResource(event);
                            handle->setCreateId(event->getCreateId());
                        }
                        mBitFlag.setBit(2);
                    }
                    else {
                        mUser->getSystem()->freeEvent(event, nullptr);
                        event = nullptr;
                    }
                }
            }

            if (event != nullptr)
                doEventActivatedCallback_(locator, event);
        }
    }
}

void UserInstance::printLogEmitFailed(const char* /*unused*/, const char* /*unused*/, ...) const {}

bool UserInstance::isDebugLogEnable(DebugLogFlag /*unused*/) const 
{
    return false;
}

void UserInstance::checkAndBreakWhenEmit_(const char* /*unused*/) {}

// NON-MATCHING: unknown reason
void UserInstance::freeEventIfFadeOrKillCalled()
{
    for (auto& event : mEventList.robustRange()) {
        if (event.getBitFlag().isOnBit(4))
            mUser->getSystem()->freeEvent(&event, &mEventList);
    }
}

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

bool UserInstance::searchAssetRecursive(Locator* locator, const char* name)
{
    locator->reset();
    if (mUser->getSystem()->isCallEnabled()) {
        ResAssetCallTable* asset_ctb1 {mUser->getUserResource()->searchAssetCallTableByName(name)};
        if (asset_ctb1 != nullptr) {
            const ResAssetCallTable* asset_ctb2 {};
            if (trySearchSwitchContainerRecursive_(&asset_ctb2, *asset_ctb1)) {
                if (asset_ctb2 != nullptr)
                    locator->setAssetCallTable(asset_ctb2);
                return asset_ctb2 != nullptr;
            }
            
            locator->setAssetCallTable(asset_ctb1);
            return true;
        }
        
    }

    return false;
}

// NON-MATCHING: bad branching
bool UserInstance::searchEmittingEvent(Handle* handle, const char* key_name) const
{
    if (key_name != nullptr) {
        {
            auto lock {sead::makeScopedLock(*mUser->getSystem()->getModuleLockObj())};
            u8 unknown;
            for (auto& event : mEventList) {
                if (event.getAssetCallTable() != nullptr) {
                    const char* asset_key_name {solveOffset<const char>(event.getAssetCallTable()->keyNamePos)};
                    if (handle != nullptr) {
                        if (strcmp(key_name, asset_key_name) == 0) {
                            handle->setResource(&event);
                            handle->setCreateId(event.getCreateId());
                            unknown = 1;
                        }
                        else {
                            unknown = 0;
                        }
                    }
                    else {
                        unknown = strcmp(key_name, asset_key_name) == 0;
                    }
                }
                else {
                    unknown = 4;
                }
                if ((unknown | 4) != 4) break;
            }

            return (unknown | 2) != 2;
        }

    }

    return false;
}

void UserInstance::changeAction(const char* name, int p1, int p2) 
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
    return mTriggerCtrlMgr.getActionNeedToCalcFlag() != 0;
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

        if (mUser->getPropertyDefinition(idx)->getType() == PropertyType::F32) {
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

        if (mUser->getPropertyDefinition(idx)->getType() != PropertyType::F32) {
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

const char* UserInstance::getUserName() const 
{
    return mUser->getUserName();
}

void UserInstance::makeDebugString(sead::BufferedSafeString* debug_str, 
                                   const DebugOperationParam& debug_op_param) const
{
    debug_str->copy(getUserName());
    if (mBitFlag.isOnBit(0)) {
        sead::DateTime* editor_setup_time {mUser->getUserResource()->getEditorSetupTime()};
        if (editor_setup_time != nullptr) {
            sead::CalendarTime calendar_time {};
            editor_setup_time->getCalendarTime(&calendar_time);
            debug_str->appendWithFormat(" (%d/%d/%d %d:%d:%d)", 
                                        calendar_time.getYear(), 
                                        calendar_time.getMonth(),
                                        calendar_time.getDay(),
                                        calendar_time.getHour(),
                                        calendar_time.getMinute(),
                                        calendar_time.getSecond());
        }
    }
    debug_str->appendWithFormat("\n");

    if (debug_op_param.getDebugUserFlag().isOnBit(16))
        makeDebugStringUserInformation(debug_str);

    if (debug_op_param.getDebugUserFlag().isOnBit(17))
        makeDebugStringAction(debug_str, debug_op_param.getDebugStringAction());

    if (debug_op_param.getDebugUserFlag().isOnBit(18))
        makeDebugStringLocalProperty(debug_str, debug_op_param.getDebugStringLocalProperty());

    makeDebugStringEvent(debug_str, debug_op_param.getDebugStringEvent());
}

void UserInstance::makeDebugStringUserInformation(sead::BufferedSafeString* debug_str) const
{
    if (debug_str != nullptr && mIUser->getUserInformation() != nullptr) {
        debug_str->appendWithFormat("-- UserInfo --\n");
        debug_str->appendWithFormat(mIUser->getUserInformation());
    }
}

// NON-MATCHING: uses 64-bit register instead of the expected 32-bit
void UserInstance::makeDebugStringAction(sead::BufferedSafeString* debug_str, 
                                         const sead::SafeString& filter) const
{
    if (debug_str != nullptr) {
        if (filter.isEmpty())
            debug_str->appendWithFormat("-- Action --\n");
        else
            debug_str->appendWithFormat("-- Action (filter [%s]) --\n", filter.cstr());
        
        for (s32 i {0}; i < mUser->getNumActionSlot(); ++i) {
            sead::FixedSafeString<64> action_slot_name;
            if (mUser->getActionSlotNameTable() != nullptr)
                action_slot_name.appendWithFormat(mUser->getActionSlotName(i));
            else
                action_slot_name.appendWithFormat(mIUser->getActionSlotName(i));

            if (!action_slot_name.isEmpty()) {
                if (!filter.isEmpty() && action_slot_name.findIndex(filter.cstr()) == -1) {
                    continue;
                }

                if (mTriggerCtrlMgr.getCurrentActionName(i) != nullptr) {
                    if (*mTriggerCtrlMgr.getCurrentActionName(i) == '\0') {
                        const char* action_slot {action_slot_name.cstr()};
                        s32 current_action_frame {mTriggerCtrlMgr.getCurrentActionFrame(i)};
                        debug_str->appendWithFormat("[%s] no action (%d)\n", 
                                                    action_slot, 
                                                    current_action_frame);
                    }
                    else {
                        const char* action_slot {action_slot_name.cstr()};
                        const char* current_action_name {mTriggerCtrlMgr.getCurrentActionName(i)};
                        s32 current_action_frame {mTriggerCtrlMgr.getCurrentActionFrame(i)};
                        debug_str->appendWithFormat("[%s] %s (%d)\n", 
                                                    action_slot, 
                                                    current_action_name, 
                                                    current_action_frame);
                    }
                }
            }
        }
    }
}

// NON-MATCHING
void UserInstance::makeDebugStringLocalProperty(sead::BufferedSafeString* debug_str,
                                                const sead::SafeString& filter) const
{
    if (debug_str != nullptr) {
        if (filter.isEmpty())
            debug_str->appendWithFormat("-- Local Property --\n");
        else
            debug_str->appendWithFormat("-- Local Property (filter [%s]) --\n", filter.cstr());
    
        for (s32 i {0}; i < mUser->getNumLocalProp(); ++i) {
            const char* property_name {""};
            PropertyDefinition* property_definition {mUser->getPropertyDefinition(i)};
            PropertyValueType* property_values {mPropertyValueArray};
            
            if (property_definition != nullptr) {
                if (property_definition->getPropertyName()->cstr() != nullptr)
                    property_name = property_definition->getPropertyName()->cstr();
            }

            if (*property_name != '\0') {
                if (!filter.isEmpty()) {
                    sead::FixedSafeStringBase<char, 64> safe_property_name {property_name};
                    if (safe_property_name.findIndex(filter.cstr()) == -1)
                        continue;
                }

                const char* entry_key {""};
                PropertyValueType value {property_values[i]};

                switch (property_definition->getType()) {
                case PropertyType::Enum:
                    entry_key = static_cast<EnumPropertyDefinition*>(property_definition)->searchEntryKeyByValue(value.valueInt);
                    debug_str->appendWithFormat("[%s] %s (%d)\n", property_name, entry_key, value.valueInt);
                    break;
                case PropertyType::S32:
                    if (value.valueInt >= 0)
                        entry_key = " ";
                    debug_str->appendWithFormat("[%s] %s%d\n", property_name, entry_key, value.valueInt);
                    break;
                case PropertyType::F32:
                    if (value.valueFloat >= 0)
                        entry_key = " ";
                    debug_str->appendWithFormat("[%s] %s%f\n", property_name, entry_key, value.valueFloat);
                    break;
                }
            }
        }
    }
} 

void UserInstance::setDebugLogFlag([[maybe_unused]] sead::BitFlag32 debug_log_flag) {}

void UserInstance::setRootMtx(const sead::Matrix34f* root_mtx)
{
    auto* raw_mtx {mRootMtx.rawMtx};
    if (raw_mtx != root_mtx) {
        auto* param {getParam()};
        if (param != nullptr && param->isSetupRom) {
            auto& connection_buffer {param->modelAssetConnectionBuffer};
            for (s32 i {0}; i < connection_buffer.size(); ++i) {
                auto& connection {connection_buffer[i]};
                if (connection.mRootMtx.rawMtx == raw_mtx) {
                    connection_buffer[i].mRootMtx.setRawMtx(root_mtx, 0);
                }
            }
        }
        mRootMtx.rawMtx = root_mtx;
        mRootMtx._0 = 0;
    }
}

void UserInstance::setRootPos(const sead::Vector3f* root_pos) 
{
    mRootPos = root_pos;
}

void UserInstance::setRandomHistory(u32 key_name_pos1, u32 key_name_pos2)
{
    auto* param {getParam()};
    s32 idx {0};
    if (param->randomHistoryBuffer.size() > 0) {
        for (s32 i {0}, j {-1}; i < param->randomHistoryBuffer.size(); ++i, j = idx) {
            auto* random_history {&param->randomHistoryBuffer[i]};
            if (random_history->prevKeyNamePos == key_name_pos1) {
                random_history->nextKeyNamePos = key_name_pos2;
                return;
            }
    
            idx = j == -1 && random_history->prevKeyNamePos == 0 ? i : j;
        }

        if (idx > -1) {
            auto* random_history {&param->randomHistoryBuffer[idx]};
            random_history->prevKeyNamePos = key_name_pos1;
            random_history->nextKeyNamePos = key_name_pos2;
        }
    }
}

u32 UserInstance::searchRandomHistory(u32 key_name_pos) const
{
    auto* param {getParam()};
    for (s32 i {0}; i < param->randomHistoryBuffer.size(); ++i) {
        auto* random_history {&param->randomHistoryBuffer[i]};
        if (random_history->prevKeyNamePos == key_name_pos)
            return random_history->nextKeyNamePos;
    }

    return 0;
}

// NON-MATCHING: WIP
void UserInstance::updateSortKey()
{
    auto& debug_op_param {mUser->getSystem()->getDebugOperationParam()};
    sead::Matrix34f bone_world_mtx {};
    sead::Vector3f vector3f {};
    if (debug_op_param.getDebugUserFlag().isOffBit(25) && mBitFlag.isOffBit(1)) {
        auto* iuser {mIUser};
        u32 num_bone {iuser->getNumBone()};
        if (num_bone < 1) {
            if (mRootPos == nullptr) {
                if (mRootMtx._0 == 0) {
                    vector3f.x = mRootMtx.rawMtx->m[0][3];
                    vector3f.y = mRootMtx.rawMtx->m[1][3];
                    bone_world_mtx.m[0][2] = mRootMtx.rawMtx->m[2][3];
                }
                else {
                    vector3f.x = mRootMtx.rawMtx->a[9];
                    vector3f.y = mRootMtx.rawMtx->a[10];
                    bone_world_mtx.m[0][2] = mRootMtx.rawMtx->a[11];
                }
            }
            else {
                vector3f.x = mRootPos->x;
                vector3f.y = mRootPos->y;
                bone_world_mtx.m[0][2] = mRootPos->z;
            }
        }
        else {
            const char* root_bone_name {iuser->getBoneName(0)};
            iuser->getBoneWorldMtx(root_bone_name, &bone_world_mtx);
            vector3f.x = bone_world_mtx.m[0][3];
            vector3f.y = bone_world_mtx.m[1][3];
            bone_world_mtx.m[0][2] = bone_world_mtx.m[2][3];
        }
        bone_world_mtx.m[0][0] = vector3f.x;
        bone_world_mtx.m[0][1] = vector3f.y;
        f32 sort_key {mIUser->getSortKey(vector3f)};
        mSortKey = sort_key;
    }
}

f32 UserInstance::getSortKey() const
{
    auto* system {mUser->getSystem()};
    auto* debug_op_param {&system->getDebugOperationParam()};
    if (debug_op_param->getDebugUserFlag().isOffBit(25) && mBitFlag.isOnBit(1))
        return INFINITY;

    return mSortKey;
}

void UserInstance::printLogContainerSelect(const Event& /*unused*/, const char* /*unused*/, ...) const {}
void UserInstance::printLogEmitFailed(const Event& /*unused*/, const char* /*unused*/, ...) const {}

const sead::SafeString& UserInstance::getContainerTypeName(const ResAssetCallTable& asset_call) const 
{
    auto& accessor {mUser->getUserResource()->getAccessor()};
    return accessor.getCallTableTypeName(asset_call);
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

void UserInstance::freeInstanceParam_(UserInstanceParam* param, [[maybe_unused]] ResMode mode) 
{
    param->modelAssetConnectionBuffer.freeBuffer();
    param->randomHistoryBuffer.freeBuffer();
}

void UserInstance::onSetupInstanceParam_([[maybe_unused]] ResMode mode, [[maybe_unused]] sead::Heap* heap) {}
bool UserInstance::doEventActivatingCallback_([[maybe_unused]] const Locator& locator)
{
    return false;
}
void UserInstance::doEventActivatedCallback_([[maybe_unused]] const Locator& locator, [[maybe_unused]] Event* event) {}
}  // namespace xlink2