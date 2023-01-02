#pragma once

#include "heap/seadHeap.h"
#include "xlink2/xlink2AssetExecutorELink.h"
#include "xlink2/xlink2UserInstanceELink.h"
#include "xlink2/xlink2UserResourceELink.h"

namespace xlink2 {
class UserResourceELink;

class SystemELink : System {
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
    // 0x7f8
    // PtclSystem* mPtclSystem;

    // 0x800
    // void*

    // 0x808
    // void*

    // 0x810
    // void*

    // 0x818
    // u32

    // 0x81c
    // u32

    // 0x820
    // u32

    // 0x824
    // u32

    // 0x828
    // u32

    // 0x82c
    // u32

    // 0x830
    // u32

    // 0x834
    // u32

    // 0x838
    // u32

    // 0x83c
    // u32

    // 0x840
    // u32

    // 0x844
    // u32

    // 0x848
    // u32

    // 0x84c
    // u32

    // 0x850
    // u32

    // 0x854
    // u32

    // 0x858
    // u32

    // 0x85c
    // u32

    // 0x860
    // u32
};
}