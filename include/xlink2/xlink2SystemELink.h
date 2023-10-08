#pragma once

#include "heap/seadHeap.h"
#include "xlink2/xlink2AssetExecutorELink.h"
#include "xlink2/xlink2UserInstanceELink.h"
#include "xlink2/xlink2UserResourceELink.h"

namespace xlink2 {
class UserResourceELink;
class UserInstanceELink;
class AssetExecutorELink;


class SystemELink : System {
    SEAD_SINGLETON_DISPOSER(SystemELink);
public:
    static ILockProxy* sLockProxy;

    SystemELink() = default;
    ~SystemELink() override;

    class SingletonDisposer;

    // void initialize(sead::ptcl::PtclSystem*, sead::Heap*, sead::Heap*, u32, ILockProxy*);

    void allocAssetExecutor(Event*) override;
    void allocHandle(sead::Heap*) override;

    UserInstanceELink* createUserInstance(UserInstance::CreateArg const&, sead::Heap*, u32);
    void createUserResource(User*, sead::Heap*) override;

    // void drawInformationEvent(sead::TextWriter*) const;
    // void drawInformationSystemDetail(sead::TextWriter*) const;
    void genMessage(sead::hostio::Context* /*unused*/){};

    u64 getEventFromPool_(u32) const override;
    ILockProxy* getModuleLockObj() const override;
    char* getModuleName() const override;
    void** getORIconString();
    u64 getResourceVersion() const override;
    u64 getUserParamNum() const override;

    void listenPropertyEvent(sead::hostio::PropertyEvent const* /*unused*/){};

    void makeDebugAssetInformationString(s32, sead::BufferedSafeString*, sead::BufferedSafeString&,
                                         sead::SafeString const&, Event*, AssetExecutorELink*,
                                         bool) const;

    // void postDrawInformation(sead::TextWriter*) const;
    // void preDrawInformation(sead::TextWriter*) const;

    void setPtclSystemState();

private:
    // sead::ptcl::PtclSystem* mPtclSystem;
    void* mPtclSystem;
    void* _19;
    void* _20;
    void* _21;
    u32 _22;
    u32 _23;
    u32 _24;
    u32 _25;
    u32 _26;
    u32 _27;
    u32 _28;
    u32 _29;
    u32 _30;
    u32 _31;
    u32 _32;
    u32 _33;
    u32 _34;
    u32 _35;
    u32 _36;
    u32 _37;
    u32 _38;
    u32 _39;
    u32 _40;
};
// static_assert(sizeof(SystemELink) == 0x69490, "Wrong size for 'xlink2::SystemELink'");

}  // namespace xlink2