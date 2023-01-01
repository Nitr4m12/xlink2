#pragma once

#include "heap/seadHeap.h"
#include "xlink2/xlink2UserInstanceSLink.h"
#include "xlink2/xlink2UserResourceSLink.h"

namespace xlink2 {
class SystemSLink : System{
    virtual ~SystemSLink();

public:
    SystemSLink() = default;

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
    void genMessage(sead::hostio::Context*);

    u64 getEventFromPool(u32) const;
    u64 getModuleLockObj() const;
    void** getModuleName() const;
    void** getORIconString();
    u64 getResourceVersion() const;
    u64 getUserParamNum() const;

    bool isEnableUserAssetInfoReadable();

    void listenPropertyEvent(sead::hostio::PropertyEvent const*);
    void stopAllEvent(s32);

private:
};
}