#include "xlink2/xlink2System.h"
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
    mGlobalPropertyDefinitions = new (heap) PropertyDefinition*[num_global_prop];
    mGlobalPropertyValues = new (heap) PropertyValueType[num_global_prop];
    mNumGlobalProperty = num_global_prop;
}

void System::fixGlobalPropertyDefinition() 
{
    mResourceBuffer->applyGlobalPropertyDefinition(this);
    if (mEditorBuffer != nullptr) {
        mEditorBuffer->applyGlobalPropertyDefinition();
    }
    mIsGlobalPropFixed = true;
}

void System::addError(Error::Type /*unused*/, const User* /*unused*/, const char* /*unused*/, ...) {
}


// ParamDefineTable* System::getParamDefineTable() const {
//     return mResourceBuffer->getParamDefineTable();
// }

// ParamDefineTable* System::getParamDefineTable(ResMode mode) const {
//     if (mode != (ResMode)1)
//         return mResourceBuffer->getParamDefineTable();

//     if (mEditorBuffer != nullptr)
//         return mEditorBuffer->getParamDefineTable();

//     return nullptr;
// }

s32 System::incrementEventCreateId_() {
    s32 event_id {mEventCreateId};
    s32 create_id {1};

    if (event_id != -1)
        create_id = event_id + 1;

    mEventCreateId = create_id;
    return event_id;
}

void System::updateContainerCount(ContainerType type, s32) {}

// bool System::isDrawTargetInstance(UserInstance* draw_target_instance) const {
//     if (mUserInstance == nullptr)
//         return mUserInstance->getSortKey();
//     return mUserInstance == draw_target_instance;
// }
bool System::isServerConnecting() const {
    return false;
}

// void System::unfixDrawInst(UserInstance * draw_instance) {
//     if (mUserInstance == draw_instance) {
//         mUserInstance = nullptr;
//     }
// }

}  // namespace xlink2