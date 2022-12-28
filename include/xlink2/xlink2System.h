#pragma once

#include "container/seadOffsetList.h"
#include "gfx/seadCamera.h"
#include "gfx/seadProjection.h"
#include "hostio/seadHostIOReflexible.h"
#include "prim/seadSafeString.h"
#include "xlink2/xlink2.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2LockProxy.h"
#include "xlink2/xlink2UserInstance.h"
namespace xlink2 {
class ContainerType;

class Error {
public:
    class Type;
};

class System {
    virtual ~System();

public:
    System() = default;

    void initSystem(sead::Heap*, sead::Heap*, u32);

    class DrawerModule {
    public:
        void begin(sead::Camera const&, sead::Projection const&);
        void drawAxis(sead::Vector3f const&, f32);
        void end();
        void setModelMatrix(sead::Matrix34f const&);
    };

    Error::Type addError(Error::Type, User const*, char const*, ...);
    Event allocEvent();
    void allocGlobalProperty(u32, sead::Heap*);
    void calc();
    f32 calcDebugDrawSortKeyThreshold() const;
    bool changeDebugOperationType(bool);
    void clearError(User const*);
    void createGlobalPropertyDefinitionTable(u32, PropertyDefinition const**, sead::Heap*);

    // void drawInformation(sead::DrawContext*, sead::TextWriter*) const;
    // void drawInformation3D(sead::DrawContext*, sead::Camera const&, sead::Projection const&,
    // sead::Viewport const&, f32) const; void drawInformationEmitter(UserInstance*,
    // sead::DrawContext*, sead::TextWriter*, sead::Camera const&, sead::Projection const&,
    // sead::Viewport const&) const; void drawInformationInstance3D(UserInstance*,
    // sead::DrawContext*, sead::TextWriter*) const; void drawInformationInstance3D(UserInstance*,
    // sead::DrawContext*, sead::TextWriter*, sead::Camera const&, sead::Projection const&,
    // sead::Viewport const&) const; void drawText3D(sead::Matrix34f const&, sead::Vector2f const&,
    // sead::SafeString const&, sead::SafeString const&, sead::TextWriter*, IUser*) const; void
    // drawText3D(sead::Matrix34f const&, sead::Vector2f const&, sead::SafeString const&,
    // sead::SafeString const&, sead::TextWriter*, sead::Camera const&, sead::Projection const&,
    // sead::Viewport const&) const;

    void dumpActiveEvents() const;
    void dumpUsers() const;

    void fixGlobalPropertyDefinition();
    void freeAllEvent(sead::OffsetList<Event>*);
    void freeAssetExecutor(AssetExecutor*);
    void freeEvent(Event*, sead::OffsetList<Event>);
    void freeGlobalProperty();

    void* getAnyone();
    void* getParamDefineTable() const;
    void* getParamDefineTable(ResMode) const;
    void* getResUserHeader(char const*);

    s32 incrementEventCreateId();

    bool isDrawTargetInstance(UserInstance*) const;
    bool isServerConnecting() const;

    void killAll();
    void killAllOneTimeEvent();

    u32 loadResource(void*);

    void makeDebugStringGlobalProperty(sead::BufferedSafeString*, sead::SafeString const&) const;
    // void postDrawInformation(sead::TextWriter*) const;
    // void postDrawInformation(sead::TextWriter*) const;
    void registUserForGlobalPropertyTrigger(User*);
    void removeUserInstance(UserInstance*);
    void requestSendPickedUserName(sead::SafeString const&);
    void resetOtameshiRequest();

    u32 searchGlobalPropertyIndex(char const*) const;
    System* searchUser(char const*, sead::Heap*, u32) const;
    s32 searchUserIgnoreHeap(char const*, User**, s32) const;
    System* searchUserOrCreate(UserInstance::CreateArg const&, sead::Heap*, u32);

    void setErrorDispFrame(s32);
    void setGlobalPropertyDefinition(u32, PropertyDefinition const*);
    void setGlobalPropertyValue(u32, s32);
    void setGlobalPropertyValue(u32, f32);

    void unfixDrawInst(UserInstance*);
    void unregistUserForGlobalPropertyTrigger(User*);

    ContainerType updateContainerCount(ContainerType, s32);
    void updateDebugDrawUserList() const;
    void updateUserForGlobalPropertyTrigger(User*);

    // void writeBlinkText(sead::SafeString const&, sead::TextWriter*) const;
    // void writeLines(sead::SafeString const&, sead::TextWriter*) const;
private:
};

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
class SystemSLink {
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
}  // namespace xlink2