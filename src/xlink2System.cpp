#include <prim/seadScopedLock.h>

#include "xlink2/xlink2System.h"
#include "math/seadMathCalcCommon.h"
#include "xlink2/xlink2EnumPropertyDefinition.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
System::System()
{
    mUserList.initOffset(0);
    setMinLargeAddressMask(reinterpret_cast<u64>(this));
}

void System::initSystem_(sead::Heap* heap, sead::Heap* primary_heap, u32 p3)
{
    mPrimaryHeap = primary_heap;
    mResourceBuffer = new (heap) ResourceBuffer;
    mMaxNumEventPool = p3;
    mNumEventPool = 0;
    mGlobalPropertyTriggerUserList.allocBuffer(0x60, heap);
    mErrorMgr = new (heap) ErrorMgr(this);
    mHoldMgr = new (heap) HoldMgr(this, heap);
}

void System::calc()
{
    if (mIsCallEnabled) {
        if (getDebugOperationParam().getDebugFlag().isOn(0b100000000000010011101111)) {
            {
                auto lock {sead::makeScopedLock(*getModuleLockObj())};
                for (auto& user : mUserList)
                    user.updateSortKey();
            }
        }
        {
            auto lock {sead::makeScopedLock(*getModuleLockObj())};
            for (auto& user : mGlobalPropertyTriggerUserList)
                for (auto& user_instance : user.getUserInstanceList())
                    user_instance.updateGlobalPropertyTriggerCtrl();
            
        }

        if (mErrorMgr != nullptr)
            mErrorMgr->calc();

        if (mHoldMgr != nullptr)
            mHoldMgr->calc();

        ++mTick;
    }
}

User* System::searchUser(const char* user_name, sead::Heap* heap, u32 idx) const
{
    {
        auto lock {sead::makeScopedLock(*getModuleLockObj())};
        if (mUserList.size() != 0)
            for (auto& user : mUserList) {
                if ((user.isHeapEqual(heap) || user.isHeapEqual(mUserCreateHeap)) && 
                    user.get8() == idx && strcmp(user.getUserName(), user_name) == 0) {
                    return &user;
                }
            }
    }
    return nullptr;
}

s32 System::searchUserIgnoreHeap(const char* user_name, User** user_ptrs, s32 idx) const
{
    s32 user_idx {0};
    {
        auto lock {sead::makeScopedLock(*getModuleLockObj())};
        for (auto& user : mUserList) {
            if (strcmp(user.getUserName(), user_name) == 0 && user_idx < idx) {
                user_ptrs[user_idx] = &user;
                ++user_idx;
            }
        }
    }
    return user_idx;
}

void System::makeDebugStringGlobalProperty(sead::BufferedSafeString* dump_str, const sead::SafeString& filter) const
{
    if (dump_str != nullptr) {
        if (filter.isEmpty())
            dump_str->appendWithFormat("-- Global Property --\n");
        else
            dump_str->appendWithFormat("-- Global Property (filter [%s]) --\n", filter.cstr());

        if (mNumGlobalProperty != 0) {
            for (u32 i {0}; i < mNumGlobalProperty; ++i) {
                const PropertyDefinition* global_prop_define {mGlobalPropertyDefinitions[i]};

                if (global_prop_define != nullptr) {
                    PropertyValueType* values {mGlobalPropertyValues};
                    const char* property_name {global_prop_define->getPropertyName()->cstr()};

                    if (*property_name != '\0') {
                        if (!filter.isEmpty()) {
                            sead::FixedSafeString<64> property_string {property_name};
                            if (!property_string.include(filter.cstr())) 
                                continue;
                        }

                        switch (global_prop_define->getType()) {
                            case PropertyType::Enum: {
                                const char* value_name {static_cast<const EnumPropertyDefinition*>(global_prop_define)->searchEntryKeyByValue(values[i].valueInt)};
                                dump_str->appendWithFormat("[%s] %s (%d)\n", property_name, value_name, values[i].valueInt);
                                break;
                            }
                            case PropertyType::S32: {
                                const char* empty {values[i].valueInt < 0 ? "" : " "};
                                dump_str->appendWithFormat("[%s] %s%d\n", property_name, empty, values[i].valueInt);
                                break;
                            }
                            case PropertyType::F32: {
                                const char* empty {values[i].valueFloat < 0.0f ? "" : " "};
                                dump_str->appendWithFormat("[%s] %s%f\n", property_name, empty, values[i].valueFloat);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

s32 System::loadResource(void* bin)
{
    setMinLargeAddressMask(reinterpret_cast<u64>(bin));
    return mResourceBuffer->load(bin, this);
}

ResUserHeader* System::getResUserHeader(const char* user_name) 
{
    return mResourceBuffer->searchResUserHeader(user_name);
}

void System::removeUserInstance(UserInstance* user_instance)
{
    unfixDrawInst_(user_instance);
    User* user {user_instance->getUser()};

    user->removeInstance(user_instance);
    if (user->getUserInstanceList().isEmpty()) {
        mUserList.erase(user);
        unregistUserForGlobalPropertyTrigger_(user);
        delete user;
    }
}

void System::unfixDrawInst_(UserInstance* user_instance)
{
    if (mDrawInstance == user_instance)
        mDrawInstance = nullptr;
}

void System::unregistUserForGlobalPropertyTrigger_(User* user)
{
    auto user_idx {mGlobalPropertyTriggerUserList.search(user)};
    if (user_idx >= 0)
        mGlobalPropertyTriggerUserList.erase(user_idx);
}

void System::allocGlobalProperty(u32 num_property, sead::Heap* heap)
{
    auto* prop_define = new (heap) const PropertyDefinition*[num_property];
    mGlobalPropertyDefinitions = prop_define;
    if (num_property != 0) {
        for (s32 i {0}; i < num_property; ++i) {
            mGlobalPropertyDefinitions[i] = nullptr;
        } 
    }
    mGlobalPropertyValues = new (heap) PropertyValueType[num_property];
    mNumGlobalProperty = num_property;
}

void System::createGlobalPropertyDefinitionTable(u32 num_property, const PropertyDefinition** buffer, sead::Heap* heap)
{
    allocGlobalProperty(num_property, heap);
    for (s32 i {0}; i != num_property; ++i)
        setGlobalPropertyDefinition(i, buffer[i]);

    mResourceBuffer->applyGlobalPropertyDefinition(this);
    if (mEditorBuffer != nullptr)
        mEditorBuffer->applyGlobalPropertyDefinition();

    mIsGlobalPropFixed = true;
}

void System::setGlobalPropertyDefinition(u32 prop_idx, const PropertyDefinition* prop_define)
{
    if (prop_define != nullptr && mNumGlobalProperty != 0 && prop_idx < mNumGlobalProperty) {
        for (u32 i {0}; i < mNumGlobalProperty; ++i) {
            if (mGlobalPropertyDefinitions[i] != nullptr) {
                auto* new_prop_name {prop_define->getPropertyName()};
                if (mGlobalPropertyDefinitions[i]->getPropertyName()->isEqual(*new_prop_name)) {
                    new_prop_name->cstr();
                    return;
                }
            }
        }
        mGlobalPropertyDefinitions[prop_idx] = prop_define;
        switch (prop_define->getType()) {
            case PropertyType::Enum:
            case PropertyType::S32:
                mGlobalPropertyValues[prop_idx].valueInt = 0;
                break;
            case PropertyType::F32:
                mGlobalPropertyValues[prop_idx].valueFloat = 0.0;
                break;
        }
    }
}

void System::fixGlobalPropertyDefinition() 
{
    mResourceBuffer->applyGlobalPropertyDefinition(this);
    if (mEditorBuffer != nullptr) {
        mEditorBuffer->applyGlobalPropertyDefinition();
    }
    mIsGlobalPropFixed = true;
}

void System::freeGlobalProperty()
{
    delete[] mGlobalPropertyDefinitions;
    delete[] mGlobalPropertyValues;
    mNumGlobalProperty = 0; 
}

void System::addError(Error::Type /*unused*/, const User* /*unused*/, const char* /*unused*/, ...) {}

void System::setGlobalPropertyValue(u32 prop_idx, s32 value)
{
    if (isCallEnabled() && 
        mGlobalPropertyValues != nullptr && 
        prop_idx < mNumGlobalProperty && 
        mGlobalPropertyDefinitions[prop_idx]->getType() != PropertyType::F32 &&
        mGlobalPropertyValues[prop_idx].valueInt != value) {
            mGlobalPropertyValues[prop_idx].valueInt = value;
            mGlobalPropertyBitfield.setBit(prop_idx);
        }
}

void System::setGlobalPropertyValue(u32 prop_idx, f32 value)
{
    if (isCallEnabled() && 
        mGlobalPropertyValues != nullptr && 
        prop_idx < mNumGlobalProperty && 
        mGlobalPropertyDefinitions[prop_idx]->getType() == PropertyType::F32 &&
        mGlobalPropertyValues[prop_idx].valueFloat != value) {
            mGlobalPropertyValues[prop_idx].valueFloat = value;
            mGlobalPropertyBitfield.setBit(prop_idx);
        }
}

s32 System::searchGlobalPropertyIndex(const char* prop_name) const
{
    for (u32 i {0}; i < mNumGlobalProperty; ++i) {
        if (mGlobalPropertyDefinitions[i] != nullptr) {
            auto* global_prop_name {mGlobalPropertyDefinitions[i]->getPropertyName()};
            if (strcmp(prop_name, global_prop_name->cstr()) == 0)
                return i;
        }
    }

    return -1;
}

s32 System::incrementEventCreateId_() 
{
    s32 event_id {mEventCreateId};
    mEventCreateId = mEventCreateId != -1 ? mEventCreateId + 1 : 1;
    
    return event_id;
}

const Event* System::allocEvent()
{
    for (u32 i {0}; i < mMaxNumEventPool; ++i) {
        auto* event {getEventFromPool_(mNumEventPool)};
        mNumEventPool = mNumEventPool + 1 < mMaxNumEventPool ? mNumEventPool + 1 : 0;

        if (event->get0x20() == 0) {
            event->initialize(incrementEventCreateId_());
            return event;
        }
    }
    
    return nullptr;
}

void System::registUserForGlobalPropertyTrigger(User* user)
{
    if (user->getUserResource()->hasGlobalPropertyTrigger()) {
        if (mGlobalPropertyTriggerUserList.search(user) == -1) {
            mGlobalPropertyTriggerUserList.pushBack(user);
        }
    }
}

void System::updateUserForGlobalPropertyTrigger(User* user)
{
    if (user->getUserResource()->hasGlobalPropertyTrigger())
        registUserForGlobalPropertyTrigger(user);
    else 
        unregistUserForGlobalPropertyTrigger_(user);

}

const ParamDefineTable* System::getParamDefineTable() const
{
    return mResourceBuffer->getParamDefineTable();
}

const ParamDefineTable* System::getParamDefineTable(ResMode res_mode) const
{
    if (res_mode != ResMode::Editor)
        return mResourceBuffer->getParamDefineTable();
    
    if (mEditorBuffer != nullptr)
        return mEditorBuffer->getParamDefineTable();

    return nullptr;
}

void System::drawInformationInstance3D_(UserInstance* user_instance, sead::DrawContext*, sead::TextWriter*) const
{
    user_instance->getIUser()->getDebugDrawCamera();
    user_instance->getIUser()->getDebugDrawProjection();
}

void System::drawInformationInstance3D_(UserInstance* user_instance, sead::DrawContext*, sead::TextWriter*,
                                const sead::Camera&, const sead::Projection&,
                                const sead::Viewport&) const 
{
#ifdef SEAD_DEBUG
#endif
}

void System::drawText3D_(const sead::Matrix34f&, const sead::Vector2f&, const sead::SafeString&,
                const sead::SafeString&, sead::TextWriter*, IUser*) const 
{
#ifdef SEAD_DEBUG
#endif
}

void System::drawText3D_(sead::Matrix34f const&, sead::Vector2f const&, sead::SafeString const&,
                sead::SafeString const&, sead::TextWriter*, sead::Camera const&,
                sead::Projection const&, sead::Viewport const&) const 
{
#ifdef SEAD_DEBUG
#endif
}

bool System::isDrawTargetInstance_(UserInstance* target_instance) const 
{
    if (mDrawInstance != nullptr)
        return mDrawInstance == target_instance;
    return target_instance->getSortKey() <= mUserSortKey;
}

void System::clearError(const User* user)
{
#ifdef SEAD_DEBUG
#endif
}

void* System::getAnyone()
{
    return nullptr;
}

void System::updateContainerCount(ContainerType type, s32) 
{
#ifdef SEAD_DEBUG
#endif
}

void System::freeAssetExecutor(AssetExecutor* asset_executor)
{
    asset_executor->onDestroy_();
    // TODO: revisit this function to see if this check can be made simpler
    if ((static_cast<s32>(asset_executor->getContainerType()) & -2) != static_cast<s32>(ContainerType::Sequence))
        asset_executor->fadeBySystem();

    asset_executor->setAssetCallTable(nullptr);
    asset_executor->setContainerType(ContainerType::Switch);
    asset_executor->set34(0);
    asset_executor->setUserInstance(nullptr);

    auto* heap {mAssetExecutorHeap};
    asset_executor->~AssetExecutor();
    heap->free(asset_executor);
}

void System::setErrorDispFrame(s32 disp_frame)
{
    if (mErrorMgr != nullptr)
        mErrorMgr->setDispFrame(disp_frame);
}

void System::killAll()
{
    {
        auto lock {sead::makeScopedLock(*getModuleLockObj())};
        for (auto& user : mUserList)
            user.killAll();
    }
}

void System::killAllOneTimeEvent()
{
    {
        auto lock {sead::makeScopedLock(*getModuleLockObj())};
        for (auto& user : mUserList)
            for (auto& instance : user.getUserInstanceList())
                instance.killAllOneTimeEvent();
    }
}

bool System::isServerConnecting() const
{
    return false;
}

void System::changeDebugOperationType(bool b1)
{
#ifdef SEAD_DEBUG
#endif
}

void System::dumpActiveEvents() const
{
    {
        auto lock {sead::makeScopedLock(*getModuleLockObj())};
        for (auto& user : mUserList) {
            for (auto& instance : user.getUserInstanceList()) {
                for (auto& event : *instance.getEventList()) {
                    s32 asset_num {event.getAliveAssetNum()};
                    asset_num = event.getFadeBySystemListAssetNum();
                    for (auto& executor : event.getAliveAssetExecutors())
                        executor.dumpDebugPrint();

                    if (asset_num != 0) {
                        for (auto& executor : event.getFadeBySystemExecutors())
                            executor.dumpDebugPrint();
                    }
                }
            }
        }
    }
}

void System::dumpUsers() const
{
    {
        auto lock {sead::makeScopedLock(*getModuleLockObj())};
        for (auto& user : mUserList) {
            for (auto& instance : user.getUserInstanceList()) {
#ifdef SEAD_DEBUG
#endif
            }
        }
    }
}

void System::requestSendPickedUserName(const sead::SafeString& /*unused*/)
{
#ifdef SEAD_DEBUG
#endif
}

System::~System()
{
    if (mResourceBuffer != nullptr) {
        delete mResourceBuffer;
        mResourceBuffer = nullptr;
    }

    if (mErrorMgr != nullptr) {
        delete mErrorMgr;
        mErrorMgr = nullptr;
    }

    if (mHoldMgr != nullptr) {
        delete mHoldMgr;
        mHoldMgr = nullptr;
    }
}

}  // namespace xlink2