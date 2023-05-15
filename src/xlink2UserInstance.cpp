#include <xlink2/xlink2UserInstance.h>

namespace xlink2 {
void UserInstance::changeAction(char const* name, int p1, int p2) {
    auto* sys = mUser->getSystem();
    if (sys->getCallEnable())
        mTriggerCtrlMgr.changeAction(name, p1, p2);
}

void UserInstance::changeAction(int p1, int p2, int p3) {
    auto* sys = mUser->getSystem();
    if (sys->getCallEnable())
        mTriggerCtrlMgr.changeAction(p1, p2, p3);
}

void UserInstance::changeInstanceParam(ResMode mode) {
    u8 _6var = _0xD0;
    if (mode != ResMode::Editor)
        _6var &= 0xfe;
    else
        _6var |= 1;
    _0xD0 = _6var;
    mTriggerCtrlMgr.setResMode(mode);
}

void UserInstance::checkAndBreakWhenEmit_(const char* /*unused*/) {}

u64 UserInstance::checkAndErrorCallInCalc(const char* /*unused*/, ...) const {
    return 1;
}

// WIP
u64 UserInstance::checkAndErrorCallWithoutSetup_(const char* p1, ...) const {
    if (!mParamsByResMode[_0xD0 & 1] || !mParamsByResMode[_0xD0 & 1]) {
        sead::BufferedSafeString d(nullptr, 100);
        d.formatV(p1, std::va_list());
        mUser->getSystem()->addError(Error::Type(0x19), mUser, "%s");
        return 0;
    }
    return 1;
}

// WIP
void UserInstance::clearAllEvent() {
    System* sys = mUser->getSystem();
    auto* lock_obj = sys->getModuleLockObj();
    lock_obj->lock();
    if (mEventList.begin() != mEventList.end()) {
    }
}

void UserInstance::doEventActivatedCallback_(const Locator& /*unused*/, Event* /*unused*/) {}

u32 UserInstance::doEventActivatingCallback_(const Locator& /*unused*/) {
    return 0;
}

void UserInstance::doOtameshiEmit_() {};

char* UserInstance::getContainerTypeName(ResAssetCallTable const& asset_call) const {
    return mUser->getUserResource()->getAccessor()->getCallTableTypeName(asset_call);
}

u64 UserInstance::getCurrentResActionIdx(s32 index) const {
    return mTriggerCtrlMgr.getCurrentResActionIdx(index);
}

u32 UserInstance::getDefaultGroup() const {
    return 0;
}

char* UserInstance::getUserName() const {
    return mUser->getUserName();
}

bool UserInstance::isCurrentActionNeedToCalc() const {
    return mTriggerCtrlMgr.get1() != 0;
}

bool UserInstance::isCurrentActionNeedToObserve(s32 index) const {
    if (mUser->getSystem()->getCallEnable())
        return mTriggerCtrlMgr.isCurrentActionNeedToObserve(index);

    return false;
}


bool UserInstance::isDebugLogEnable(DebugLogFlag /*unused*/) const {
    return false;
}

void UserInstance::onReset_() {}
void UserInstance::onSetupInstanceParam_(ResMode /*unused*/, sead::Heap* /*unused*/) {}

void UserInstance::printLogEmitFailed(char const* /*unused*/, char const* /*unused*/, ...) const {}
void UserInstance::printLogEmitFailed(Event const& /*unused*/, char const* /*unused*/, ...) const {}
void UserInstance::printLogFadeOrKill(Event const* /*unused*/, char const* /*unused*/, ...) const {}
void UserInstance::printLogSearchAsset_(bool /*unused*/, char const* /*unused*/, ...) const {}

}  // namespace xlink2