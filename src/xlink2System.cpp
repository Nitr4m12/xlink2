#include "xlink2/xlink2System.h"

namespace xlink2 {
ResUserHeader* System::getResUserHeader(const char* user_name) 
{
    return mResourceBuffer->searchResUserHeader(user_name);
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

ContainerType System::updateContainerCount(ContainerType p1, s32 p2) {
    return p1;
}

}  // namespace xlink2