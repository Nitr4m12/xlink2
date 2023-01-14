#include <xlink2/xlink2UserInstance.h>

namespace xlink2 {
u64 UserInstance::checkAndErrorCallInCalc(const char* /*unused*/, ...) const {
    return 1;
}

void UserInstance::doEventActivatedCallback_(const Locator& /*unused*/, Event* /*unused*/) {}

u32 UserInstance::doEventActivatingCallback_(const Locator& /*unused*/) {
    return 0;
}

u32 UserInstance::getDefaultGroup() const {
    return 0;
}

char* UserInstance::getUserName() const {
    return mUser->getUserName();
}

bool UserInstance::isCurrentActionNeedToCalc() const {
    return _15 != 0;
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