#pragma once

#include <heap/seadHeap.h>

#include "xlink2/xlink2EventSLink.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2UserInstanceSLink.h"

namespace aal {
class System;
}

namespace xlink2 {
static sead::SafeString sModuleNameSLink {"SLink2"};
static sead::SafeString sORIconStringSLink {""};

class SystemSLink : public System {
    SEAD_SINGLETON_DISPOSER(SystemSLink);

public:
    static ILockProxy* sLockProxy;

    SystemSLink();
    ~SystemSLink() override;

    void initialize(aal::System* aal_system, sead::Heap* heap, 
                    sead::Heap* primary_heap, u32 max_num_event_pool, 
                    ILockProxy* lock);

    UserInstanceSLink* createUserInstance(const UserInstanceSLink::CreateArgSLink& arg, 
                                          sead::Heap* heap, u32 i1);
    UserResource* createUserResource(User* user, sead::Heap* heap) override;

    void allocHandle(sead::Heap* heap) override;
    AssetExecutor* allocAssetExecutor(Event* event) override;

    u32 getResourceVersion() const override;
    sead::SafeString* getModuleName() const override;
    u32 getUserParamNum() const override;

    bool isEnableUserAssetInfoReadable();

    void stopAllEvent(s32);

#ifdef SEAD_DEBUG
    void genMessage(sead::hostio::Context* context) override;
    void listenPropertyEvent(const sead::hostio::PropertyEvent* event) override;
#else
    void genMessage([[maybe_unused]] sead::hostio::Context*);
    void listenPropertyEvent([[maybe_unused]] const sead::hostio::PropertyEvent*);
#endif

    sead::SafeString* getORIconString();

    Event* getEventFromPool_(u32 idx) const override;

    void drawInformationSystemDetail_([[maybe_unused]] sead::TextWriter* text_writer) const override;
    void drawInformationEvent_([[maybe_unused]] sead::TextWriter* text_writer) const override;
    void drawInformationEmitter_([[maybe_unused]] UserInstance* user_instance, 
                                 [[maybe_unused]] sead::DrawContext* draw_context, 
                                 [[maybe_unused]] sead::TextWriter* text_writer,
                                 [[maybe_unused]] const sead::Camera& camera, 
                                 [[maybe_unused]] const sead::Projection& projection,
                                 [[maybe_unused]] const sead::Viewport& viewport) const override;

    ILockProxy* getModuleLockObj() const override;

private:
    bool mIsAllocatedLock {false};
    bool _15 {true};
    aal::System* mAalSystem {};
    void* _16 {};
    void* _17 {};
    EventSLink* mpEventPool {};
    void* _19 {};
};
static_assert(sizeof(SystemSLink) == 0x820, "'xlink2::SystemSLink' size mismatch");

}  // namespace xlink2