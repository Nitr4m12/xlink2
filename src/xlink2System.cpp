#include <prim/seadScopedLock.h>

#include "xlink2/xlink2System.h"
#include "math/seadMathCalcCommon.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
void System::initSystem_(sead::Heap* heap, sead::Heap* primary_heap, u32 p3)
{
    mPrimaryHeap = primary_heap;
    mResourceBuffer = new (heap) ResourceBuffer;
    _15 = p3;
    _16 = 0;
    mGlobalPropertyTriggerUserList.allocBuffer(0x60, heap);
    mErrorMgr = new (heap) ErrorMgr(this);
    mHoldMgr = new (heap) HoldMgr(this, heap);
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

    user->getUserInstanceList()->erase(user_instance);
    if (user->getUserInstanceList()->isEmpty()) {
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

// WIP
void System::allocGlobalProperty(u32 num_global_prop, sead::Heap* heap)
{
    mGlobalPropertyDefinitions = new (heap) const PropertyDefinition*[num_global_prop];
    mGlobalPropertyValues = new (heap) PropertyValueType[num_global_prop];
    mNumGlobalProperty = num_global_prop;
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

s32 System::incrementEventCreateId_() {
    s32 event_id {mEventCreateId};
    s32 create_id {1};

    if (event_id != -1)
        create_id = event_id + 1;

    mEventCreateId = create_id;
    return event_id;
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

bool System::isServerConnecting() const {
    return false;
}

}  // namespace xlink2