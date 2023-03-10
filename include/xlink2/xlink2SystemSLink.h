#pragma once

#include "heap/seadHeap.h"
#include "xlink2/xlink2UserInstanceSLink.h"
#include "xlink2/xlink2UserResourceSLink.h"

namespace xlink2 {
class UserResourceSLink;
class SystemSLink : System {
    SEAD_SINGLETON_DISPOSER(SystemSLink);
public:
    static ILockProxy* sLockProxy;

    SystemSLink();
    ~SystemSLink() override;

    class SingletonDisposer;

    // void initialize(aal::System*, sead::Heap*, sead::Heap*, u32, ILockProxy*);

    void* allocAssetExecutor(Event*);
    void allocHandle(sead::Heap*);

    UserInstanceSLink* createUserInstance(UserInstance::CreateArg const&, sead::Heap*, u32);
    UserResourceSLink* createUserResource(User*, sead::Heap*);

    // void drawInformationEmitter(UserInstance*, sead::DrawContext*, sead::TextWriter*,
    //                             sead::Camera const&, sead::Projection const&,
    //                             sead::Viewport const&) const;
    // void drawInformationEvent(sead::TextWriter*) const;
    // void drawInformationSystemDetail(sead::TextWriter*) const;
    void genMessage(sead::hostio::Context* /*unused*/){};

    u64 getEventFromPool(u32) const;
    ILockProxy* getModuleLockObj() const;
    void** getModuleName() const;
    void** getORIconString();
    u64 getResourceVersion() const;
    u64 getUserParamNum() const;

    bool isEnableUserAssetInfoReadable() const;

    void listenPropertyEvent(sead::hostio::PropertyEvent const* /*unused*/){};
    void stopAllEvent(s32);

private:
    void* _15;
    void* _16;
    void* _17;
    void* _18;
    void* _19;
};
}  // namespace xlink2