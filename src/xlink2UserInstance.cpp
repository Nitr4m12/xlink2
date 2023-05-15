#include <xlink2/xlink2UserInstance.h>
#include "xlink2/xlink2System.h"

namespace xlink2 {
u64 UserInstance::checkAndErrorCallInCalc(const char* /*unused*/, ...) const {
    return 1;
}

void UserInstance::printLogFadeOrKill(Event const* /*unused*/, char const* /*unused*/, ...) const {}

// NON-MATCHING: One instruction missing
void UserInstance::preCalc() {
    if (unkCheck())
        mTriggerCtrlMgr.calc();
}

void UserInstance::doOtameshiEmit_(){};

// NON-MATCHING: One instruction missing
void UserInstance::postCalc() {
    if (unkCheck()) {
        onPostCalc_();
        mValueChangedBitfield = 0;
        mParamType = mParamType & 0xfb;
    }
}

void UserInstance::reset() {
    clearAllEvent();
    mTriggerCtrlMgr.reset();
    onReset_();
}

void UserInstance::killAll() {
    clearAllEvent();
    mTriggerCtrlMgr.reset();
}

// NON-MATCHING: Two instructions missing
void UserInstance::setIsActive(bool p1) {
    auto unk1 = p1 ^ (mParamType & 2);
    auto unk2 = unk1 >> 1;
    if (!unk2) {
        if (p1)
            mTriggerCtrlMgr.notifyActive();
        else
            sleep();
        u8 unk;
        if (!p1)
            unk = mParamType | 2;
        else
            unk = mParamType & 0xfd;
        mParamType = unk;
    }
}

void UserInstance::clearAllEvent() {
    {
        auto lock = sead::makeScopedLock(*mUser->getSystem()->getModuleLockObj());
        for (auto& event : mEventList)
            event.kill();

        mUser->getSystem()->freeAllEvent(&mEventList);
    }
}

bool UserInstance::isSetupRomInstanceParam_() const {
    if (mParamsByResMode[(s32)ResMode::Normal])
        return mParamsByResMode[(s32)ResMode::Normal]->isSetupRom;
    return false;
}

void UserInstance::setupEditorInstanceParam() {
    auto* heap = mUser->getSystem()->getPrimaryHeap();

    if (mParamsByResMode[(s32)ResMode::Editor])
        freeInstanceParam_(mParamsByResMode[(s32)ResMode::Editor], ResMode::Editor);

    mParamsByResMode[(s32)ResMode::Editor] = allocInstanceParam_(heap);
    setupInstanceParam_(ResMode::Editor, heap);
    mTriggerCtrlMgr.allocAndSetupCtrlParam(ResMode::Editor, heap);
}

void UserInstance::changeInstanceParam(ResMode mode) {
    u8 param_type = mParamType;
    if (mode != ResMode::Editor)
        param_type &= 0xfe;
    else
        param_type |= 1;
    mParamType = param_type;
    mTriggerCtrlMgr.setResMode(mode);
}

// NON-MATCHING: One instruction missing
void UserInstance::linkPropertyDefinitionToValueStruct(u32 index,
                                                       const PropertyDefinition* prop_define) {
    if (prop_define->getType() == PropertyType::F32)
        mPropertyValueArray[index] = 0.0;
}

bool UserInstance::isInstanceParamValid() const {
    if (mParamsByResMode[mParamType & 1])
        return mParamsByResMode[mParamType & 1]->isSetupRom;
    return false;
}

// WIP
ModelAssetConnection* UserInstance::getModelAssetConnection(u32 index) const {
    auto* param = mParamsByResMode[mParamType & 1];
    if (param && param->isSetupRom) {
        if (param->numModelAssetConnection <= index)
            return param->modelAssetConnections;
        return &param->modelAssetConnections[index];
    }
    return nullptr;
}

// WIP
u64 UserInstance::checkAndErrorCallWithoutSetup_(const char* p1, ...) const {
    if (!mParamsByResMode[mParamType & 1] || !mParamsByResMode[mParamType & 1]) {
        sead::BufferedSafeString d(nullptr, 100);
        d.formatV(p1, std::va_list());
        mUser->getSystem()->addError(Error::Type(0x19), mUser, "%s");
        return 0;
    }
    return 1;
}

void UserInstance::printLogSearchAsset_(bool /*unused*/, char const* /*unused*/, ...) const {}

void UserInstance::printLogEmitFailed(char const* /*unused*/, char const* /*unused*/, ...) const {}

bool UserInstance::isDebugLogEnable(DebugLogFlag /*unused*/) const {
    return false;
}

void UserInstance::checkAndBreakWhenEmit_(const char* /*unused*/) {}

u64 UserInstance::getCurrentResActionIdx(s32 index) const {
    return mTriggerCtrlMgr.getCurrentResActionIdx(index);
}

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

bool UserInstance::isCurrentActionNeedToCalc() const {
    return mTriggerCtrlMgr.get1() != 0;
}

bool UserInstance::isCurrentActionNeedToObserve(s32 index) const {
    if (mUser->getSystem()->getCallEnable())
        return mTriggerCtrlMgr.isCurrentActionNeedToObserve(index);

    return false;
}

char* UserInstance::getUserName() const {
    return mUser->getUserName();
}

void UserInstance::printLogEmitFailed(Event const& /*unused*/, char const* /*unused*/, ...) const {}

char* UserInstance::getContainerTypeName(ResAssetCallTable const& asset_call) const {
    return mUser->getUserResource()->getAccessor()->getCallTableTypeName(asset_call);
}

u32 UserInstance::getDefaultGroup() const {
    return 0;
}

void UserInstance::onReset_() {}
void UserInstance::onSetupInstanceParam_(ResMode /*unused*/, sead::Heap* /*unused*/) {}
bool UserInstance::doEventActivatingCallback_(const Locator& /*unused*/) {
    return false;
}
void UserInstance::doEventActivatedCallback_(const Locator& /*unused*/, Event* /*unused*/) {}

bool UserInstance::unkCheck() {
    return !((mParamType >> 1) & 1) && mUser->getSystem()->getCallEnable();
}

}  // namespace xlink2