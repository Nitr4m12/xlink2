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

    void* allocAssetExecutor(Event*);
    void allocHandle(sead::Heap*);

    UserInstanceELink* createUserInstance(UserInstance::CreateArg const&, sead::Heap*, u32);
    UserResourceELink* createUserResource(User*, sead::Heap*);

    // void drawInformationEvent(sead::TextWriter*) const;
    // void drawInformationSystemDetail(sead::TextWriter*) const;
    void genMessage(sead::hostio::Context* /*unused*/){};

    u64 getEventFromPool(u32) const;
    ILockProxy* getModuleLockObj() const;
    void** getModuleName() const;
    void** getORIconString();
    u64 getResourceVersion() const;
    u32 getUserParamNum() const;

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
}  // namespace xlink2