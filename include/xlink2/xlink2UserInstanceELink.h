#pragma once

#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class HandleELink;
class IEventCallbackELink;
class PtclResourceAccessorELink;
class ResourceAccessorELink;
class UserResourceELink;
class UserInstanceELink;

class UserInstanceELink : public UserInstance {
public:
    UserInstanceELink(const UserInstance::CreateArg&, System*, User*, sead::Heap*);
    ~UserInstanceELink() override;

    void searchAndEmit(const char* asset_key_name);
    void searchAndEmit(const char* asset_key_name, HandleELink* handle);

    void emit(const Locator& locator);
    void emit(const Locator& locator, HandleELink* handle);

    void searchAndHold(const char* name);
    void searchAndHold(const char* name, HandleELink* handle);

    void fadeIfLoopEffect();

    const ResourceAccessorELink& getResourceAccessor() const;
    UserResourceELink* getResourceELink() const;

    void onPostCalc_() override;
    void onReset_() override;
    void onDestroy_() override;

    UserInstanceParam* allocInstanceParam_(sead::Heap* heap) override;
    void freeInstanceParam_(UserInstanceParam* param, ResMode res_mode) override;

    void onSetupInstanceParam_(ResMode res_mode, sead::Heap* heap) override;

    void initModelAssetConnection_(ResMode res_mode, const ParamDefineTable* pdt, sead::Heap* heap) override;

    void makeDebugStringEvent(sead::BufferedSafeString* event_name, const sead::SafeString& filter_name) const override;

    u32 getDefaultGroup() const override;

    IEventCallbackELink* getEventCallback() const { return mEventCallback; }

    PtclResourceAccessorELink* getPtclResourceAccessor() const { return mPtclResourceAccessor; }

private:
    IEventCallbackELink* mEventCallback {};
    s16 _0xf8 {-1};
    u8 mDefaultGroup {0};
    PtclResourceAccessorELink* mPtclResourceAccessor {};
};
static_assert(sizeof(UserInstanceELink) == 0x108, "xlink2::UserInstanceELink size mismatch");

}  // namespace xlink2