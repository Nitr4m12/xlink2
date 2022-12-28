#pragma once

#include "heap/seadHeap.h"
#include "xlink2/xlink2AssetExecutorELink.h"
#include "xlink2/xlink2UserInstanceELink.h"
#include "xlink2/xlink2UserResourceELink.h"

namespace xlink2 {
class SystemELink {
    virtual ~SystemELink();

public:
    SystemELink() = default;

    class SingletonDisposer;

    // void initialize(sead::ptcl::PtclSystem*, sead::Heap*, sead::Heap*, u32, ILockProxy*);

    void* allocAssetExecutor(Event*);
    void allocHandle(sead::Heap*);

    void* createInstance(sead::Heap*);
    UserInstanceELink* createUserInstance(UserInstance::CreateArg const&, sead::Heap*, u32);
    UserResourceELink* createUserResource(User*, sead::Heap*);

    void deleteInstance();
    // void drawInformationEvent(sead::TextWriter*) const;
    // void drawInformationSystemDetail(sead::TextWriter*) const;
    void genMessage(sead::hostio::Context*);

    u64 getEventFromPool(u32) const;
    u64 getModuleLockObj() const;
    void** getModuleName() const;
    void** getORIconString();
    u64 getResourceVersion() const;
    u64 getUserParamNum() const;

    void listenPropertyEvent(sead::hostio::PropertyEvent const*);

    void makeDebugAssetInformationString(s32, sead::BufferedSafeString*, sead::BufferedSafeString&,
                                         sead::SafeString const&, Event*, AssetExecutorELink*,
                                         bool) const;

    // void postDrawInformation(sead::TextWriter*) const;
    // void preDrawInformation(sead::TextWriter*) const;

    void setPtclSystemState();

private:
};
}