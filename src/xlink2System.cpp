#include "xlink2/xlink2System.h"

namespace xlink2 {
void System::addError(Error::Type /*unused*/, const User* /*unused*/, const char* /*unused*/, ...) {
}

void System::fixGlobalPropertyDefinition() {
    mResourceBuffer->applyGlobalPropertyDefinition(this);
    if (mEditorBuffer != nullptr) {
        mEditorBuffer->applyGlobalPropertyDefinition();
    }
    mIsGlobalPropFixed = true;
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

ResUserHeader* System::getResUserHeader(const char* p1) {
    return mResourceBuffer->searchResUserHeader(p1);
}

void System::incrementEventCreateId_() {
    if (mCurrentEventId != -1)
        mCurrentEventId += 1;
    else
        mCurrentEventId = 1;
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