#pragma once

#include <container/seadOffsetList.h>
#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <hostio/seadHostIONode.h>
#include <hostio/seadHostIOReflexible.h>
#include <prim/seadSafeString.h>
#include <container/seadPtrArray.h>

#include "xlink2/xlink2AssetExecutor.h"
#include "xlink2/xlink2ContainerBase.h"
#include "xlink2/xlink2ContainerType.h"
#include "xlink2/xlink2EditorBuffer.h"
#include "xlink2/xlink2Error.h"
#include "xlink2/xlink2ErrorMgr.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2HoldMgr.h"
#include "xlink2/xlink2LockProxy.h"
#include "xlink2/xlink2PropertyDefinition.h"
#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2ResourceBuffer.h"
#include "xlink2/xlink2User.h"

namespace xlink2 {
class ContainerBase;
class Event;
class EditorBuffer;
class ErrorMgr;
class HoldMgr;
class ResourceBuffer;
class UserInstance;

class System : sead::hostio::Node {
public:
    System() = default;

    virtual void drawInformation();     // virtual void drawInformation(sead::DrawContext*, sead::TextWriter*) const;
    virtual void drawInformation3D();   // virtual void drawInformation3D(sead::DrawContext*, sead::Camera const&, sead::Projection const&,
                                        // sead::Viewport const&, f32) const;
    virtual void createUserResource(User*, sead::Heap*) = 0;
    virtual void allocHandle(sead::Heap*) = 0;
    virtual u64 getUserParamNum() const = 0;
    virtual char* getModuleName() const = 0;
    virtual void allocAssetExecutor(Event*) = 0;
    virtual ILockProxy* getModuleLockObj() const = 0;
    virtual u64 getResourceVersion() const = 0;
    virtual ~System();
    virtual u64 getEventFromPool_(u32) const = 0;
    virtual void preDrawInformation_(); // virtual void preDrawInformation_(sead::TextWriter*) const;
    virtual void postDrawInformation_(); // virtual void postDrawInformation_(sead::TextWriter*) const;
    virtual void drawInformationSystemDetail_() const = 0; // virtual void drawInformationSystemDetail_(sead::TextWriter*) const = 0;
    virtual void drawInformationEvent_() const = 0; // virtual void drawInformationEvent_(sead::TextWriter*) const = ;
    virtual void drawInformationEmitter_() const;   // void drawInformationEmitter(UserInstance*, sead::DrawContext*, sead::TextWriter*,
                                                    // sead::Camera const&, sead::Projection const&, sead::Viewport const&) const;

    // void drawInformationInstance3D(UserInstance*, sead::DrawContext*, sead::TextWriter*) const;

    // void drawInformationInstance3D(UserInstance*, sead::DrawContext*, sead::TextWriter*,
    // sead::Camera const&, sead::Projection const&, sead::Viewport const&) const;

    // void drawText3D(sead::Matrix34f const&, sead::Vector2f const&, sead::SafeString const&,
    // sead::SafeString const&, sead::TextWriter*, IUser*) const;

    // void drawText3D(sead::Matrix34f const&, sead::Vector2f const&, sead::SafeString const&,
    // sead::SafeString const&, sead::TextWriter*, sead::Camera const&, sead::Projection const&,
    // sead::Viewport const&) const;

    void initSystem(sead::Heap*, sead::Heap*, u32);

    class DrawerModule {
    public:
        void begin(sead::Camera const&, sead::Projection const&);
        void drawAxis(sead::Vector3f const&, f32);
        void end();
        void setModelMatrix(sead::Matrix34f const&);
    };

    void addError(Error::Type /*unused*/, const User* /*unused*/, const char* /*unused*/, ...);
    Event allocEvent();
    void allocGlobalProperty(u32, sead::Heap*);
    void calc();
    f32 calcDebugDrawSortKeyThreshold() const;
    bool changeDebugOperationType(bool);
    void clearError(User const*);
    void createGlobalPropertyDefinitionTable(u32, PropertyDefinition const**, sead::Heap*);

    void dumpActiveEvents() const;
    void dumpUsers() const;

    void fixGlobalPropertyDefinition();
    void freeAllEvent(sead::OffsetList<Event>*);
    void freeAssetExecutor(AssetExecutor*);
    void freeEvent(Event*, sead::OffsetList<Event>);
    void freeGlobalProperty();

    void* getAnyone();
    ParamDefineTable* getParamDefineTable() const;
    ParamDefineTable* getParamDefineTable(ResMode mode) const;
    void* getResUserHeader(char const*);

    void incrementEventCreateId_();

    bool isDrawTargetInstance(UserInstance* draw_target_instance) const;
    bool isServerConnecting() const;

    void killAll();
    void killAllOneTimeEvent();

    u32 loadResource(void*);

    void makeDebugStringGlobalProperty(sead::BufferedSafeString*, sead::SafeString const&) const;
    void registUserForGlobalPropertyTrigger(User*);
    void removeUserInstance(UserInstance*);
    void requestSendPickedUserName(sead::SafeString const& /*unused*/){};
    void resetOtameshiRequest();

    u32 searchGlobalPropertyIndex(char const*) const;
    System* searchUser(char const*, sead::Heap*, u32) const;
    s32 searchUserIgnoreHeap(char const*, User**, s32) const;
    // System* searchUserOrCreate(UserInstance::CreateArg const&, sead::Heap*, u32);

    void setErrorDispFrame(s32);
    void setGlobalPropertyDefinition(u32, PropertyDefinition const*);
    void setGlobalPropertyValue(u32, s32);
    void setGlobalPropertyValue(u32, f32);

    void unfixDrawInst(UserInstance*);
    void unregistUserForGlobalPropertyTrigger(User*);

    ContainerType updateContainerCount(ContainerType, s32);
    void updateDebugDrawUserList() const;
    void updateUserForGlobalPropertyTrigger(User*);

    sead::Heap* getUserHeap() { return mUserHeap; }
    EditorBuffer* getEditorBuffer() { return mEditorBuffer; }
    sead::Heap* getPrimaryHeap() { return mPrimaryHeap; }

    // void writeBlinkText(sead::SafeString const&, sead::TextWriter*) const;
    // void writeLines(sead::SafeString const&, sead::TextWriter*) const;

    bool isCallEnable() const { return mCallEnable; }

protected:
    ResourceBuffer* mResourceBuffer;
    sead::OffsetList<User> mUserList;
    void* _1;
    // s32 - 0x2c?
    s32 _2;
    s32 mCurrentEventId;
    u8 _3;
    u32 mMaxGlobalPropertyValues;
    const PropertyDefinition** mGlobalPropertyDefinitions;
    float* mGlobalPropertyValues;
    u64 mGlobalPropertyValueUsedBitfield;
    u8 _4;
    ErrorMgr* mErrorMgr;
    HoldMgr* mHoldMgr;
    u32 _5;
    u8 mCallEnable;
    sead::Heap* mUserHeap;
    u32 _6;
    sead::PtrArrayImpl mGlobalPropertyTriggerUserList;
    sead::Random mRandom;
    sead::Heap* mXlinkContainerHeap;
    sead::Heap* mXlinkAssetExecutorHeap;
    sead::Heap* mPrimaryHeap;
    EditorBuffer* mEditorBuffer;
    s32 mTick;
    u32 _7;
    sead::ListImpl mListImpl;
    void* _9;
    void* _10;
    DebugOperationParam mDebugOperationParam;
    DebugOperationParam mDebugOperationParam2;
    u8 _11;
    void* _12;
    void* _13;
    UserInstance* mUserInstance;
    u8 _14;
};
}  // namespace xlink2