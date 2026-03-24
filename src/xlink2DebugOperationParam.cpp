#include "xlink2/xlink2DebugOperationParam.h"

namespace xlink2 {
DebugOperationParam::DebugOperationParam()
{
    mDebugUserFlag = 0;
    mAxisScale = 1.0f;
    mTextScale = 1.0f;
    mCharacterDisplayOffsetSystem.set(0, 0);
    mCharacterDisplayOffsetUser.set(0, 0);
    mDebugStringUser.clear();
    mDebugStringAction.clear();
    mDebugLocalStringProperty.clear();
    mDebugStringEvent.clear();
    mKeyName.clear();
    mPrintFlag = 0;
    mDebugStringGlobalProperty.clear();
    mFixedGlobalProperty = 0.0f;
    mBreakWhenEmit = false;
    mBreakTargetOnly = false;
    mDebugUserFlag.set(0x70000);
}
}