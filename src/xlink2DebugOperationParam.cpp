#include "xlink2/xlink2DebugOperationParam.h"

namespace xlink2 {
DebugOperationParam::DebugOperationParam()
{
    mDebugFlag = 0;
    mAxisScale = 1.0f;
    mTextScale = 1.0f;
    mCharacterDisplayOffsetSystem.set(0, 0);
    mCharacterDisplayOffsetUser.set(0, 0);
    mDebugUser.clear();
    mDebugAction.clear();
    mDebugLocalProperty.clear();
    mDebugEvent.clear();
    mKeyName.clear();
    mPrintFlag = 0;
    mDebugGlobalProperty.clear();
    mFixedGlobalProperty = 0.0f;
    mBreakWhenEmit = false;
    mBreakTargetOnly = false;
    mDebugFlag.set(0x70000);
}
}