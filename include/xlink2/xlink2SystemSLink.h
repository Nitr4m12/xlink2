#pragma once

#include "heap/seadHeap.h"
#include "xlink2/xlink2UserInstanceSLink.h"
#include "xlink2/xlink2UserResourceSLink.h"

namespace aal {
class System;
}

namespace sead {
class DrawContext;
}

namespace xlink2 {
class UserResourceSLink;
class SystemSLink : public System {
    SEAD_SINGLETON_DISPOSER(SystemSLink);

public:
    static ILockProxy* sLockProxy;

    SystemSLink();
    ~SystemSLink() override;

    void initialize(aal::System*, sead::Heap*, sead::Heap*, u32, ILockProxy*);

    UserInstanceSLink* createUserInstance(UserInstance::CreateArg const&, sead::Heap*, u32);
    void createUserResource(User*, sead::Heap*) override;

    void allocHandle(sead::Heap*) override;
    void allocAssetExecutor(Event*) override;

    u64 getResourceVersion() const override;
    sead::SafeString* getModuleName() const override;
    u32 getUserParamNum() const override;

    bool isEnableUserAssetInfoReadable() const;

    void stopAllEvent(s32);

#ifdef SEAD_DEBUG
    void genMessage(sead::hostio::Context* context) override;
    void listenPropertyEvent(const sead::hostio::PropertyEvent* event) override;
#else
    void genMessage(sead::hostio::Context* /*unused*/);
    void listenPropertyEvent(sead::hostio::PropertyEvent const* /*unused*/);
#endif

    sead::SafeString* getORIconString();

    Event* getEventFromPool_(u32) const override;

    void drawInformationSystemDetail_(sead::TextWriter*) const override;
    void drawInformationEvent_(sead::TextWriter*) const override;
    void drawInformationEmitter(UserInstance*, sead::DrawContext*, sead::TextWriter*,
                                sead::Camera const&, sead::Projection const&,
                                sead::Viewport const&) const;

    ILockProxy* getModuleLockObj() const override;

private:
    void* _15;
    void* _16;
    void* _17;
    void* _18;
    void* _19;
};
// static_assert(sizeof(SystemSLink) == 0x820, "Wrong size for 'xlink2::SystemSLink'");

}  // namespace xlink2