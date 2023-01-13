#pragma once

#include "heap/seadHeap.h"
#include "xlink2/xlink2UserInstanceSLink.h"
#include "xlink2/xlink2UserResourceSLink.h"

namespace xlink2 {
class UserResourceSLink;
class SystemSLink : System {
    ~SystemSLink() override;

public:
    SystemSLink();

    class SingletonDisposer;

    // void initialize(aal::System*, sead::Heap*, sead::Heap*, u32, ILockProxy*);

    void* allocAssetExecutor(Event*);
    void allocHandle(sead::Heap*);

    void* createInstance(sead::Heap*);
    UserInstanceSLink* createUserInstance(UserInstance::CreateArg const&, sead::Heap*, u32);
    UserResourceSLink* createUserResource(User*, sead::Heap*);

    void deleteInstance();
    // void drawInformationEmitter(UserInstance*, sead::DrawContext*, sead::TextWriter*,
    //                             sead::Camera const&, sead::Projection const&,
    //                             sead::Viewport const&) const;
    // void drawInformationEvent(sead::TextWriter*) const;
    // void drawInformationSystemDetail(sead::TextWriter*) const;
    void genMessage(sead::hostio::Context* /*unused*/){};

    u64 getEventFromPool(u32) const;
    u64 getModuleLockObj() const;
    void** getModuleName() const;
    void** getORIconString();
    u64 getResourceVersion() const;
    u64 getUserParamNum() const;

    bool isEnableUserAssetInfoReadable();

    void listenPropertyEvent(sead::hostio::PropertyEvent const* /*unused*/){};
    void stopAllEvent(s32);

private:
    // 0x7f4
    // u16

    // 0x7f8
    // System* mSystem;

    // 0x800
    // void*

    // 0x808
    // void*

    // 0x810
    // void*

    // 0x818
    // void*
};
}  // namespace xlink2