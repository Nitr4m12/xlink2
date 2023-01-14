#pragma once

#include "container/seadOffsetList.h"
#include "gfx/seadCamera.h"
#include "gfx/seadProjection.h"
#include "hostio/seadHostIOReflexible.h"
#include "prim/seadSafeString.h"

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

class System {
public:
    System() = default;
    virtual ~System();

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

    // void drawInformation(sead::DrawContext*, sead::TextWriter*) const;

    // void drawInformation3D(sead::DrawContext*, sead::Camera const&, sead::Projection const&,
    // sead::Viewport const&, f32) const;

    // void drawInformationEmitter(UserInstance*, sead::DrawContext*, sead::TextWriter*,
    // sead::Camera const&, sead::Projection const&, sead::Viewport const&) const;

    // void drawInformationInstance3D(UserInstance*, sead::DrawContext*, sead::TextWriter*) const;

    // void drawInformationInstance3D(UserInstance*, sead::DrawContext*, sead::TextWriter*,
    // sead::Camera const&, sead::Projection const&, sead::Viewport const&) const;

    // void drawText3D(sead::Matrix34f const&, sead::Vector2f const&, sead::SafeString const&,
    // sead::SafeString const&, sead::TextWriter*, IUser*) const;

    // void drawText3D(sead::Matrix34f const&, sead::Vector2f const&, sead::SafeString const&,
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
    // void postDrawInformation_(sead::TextWriter*) const;
    // void postDrawInformation_(sead::TextWriter*) const;
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

    // void writeBlinkText(sead::SafeString const&, sead::TextWriter*) const;
    // void writeLines(sead::SafeString const&, sead::TextWriter*) const;

private:
    ResourceBuffer* mResourceBuffer;
    sead::ListNode* mListNode;
    void* _0;
    s32 _1;
    s32 _2;
    void* _3;
    // s32 - 0x2c?
    s32 _4;
    s32 mEventCreateId;
    u8 _5;
    u32 _6;
    void* _7;
    void* _8;
    void* _9;
    u8 _10;
    ErrorMgr* mErrorMgr;
    HoldMgr* mHoldMgr;
    u32 _11;
    u8 _12;
    sead::Heap* mHeap1;
    u32 _13;
    sead::PtrArrayImpl* mPtrArrayImpl;
    void* _14;
    sead::Random* mRandom;
    ContainerBase* xlinkContainer;
    AssetExecutor* xlinkAssetExecutor;
    void* _17;
    sead::Heap* mHeap2;
    EditorBuffer* mEditorBuffer;
    s32 _18;
    u32 _19;
    sead::ListNode* mListNode2;
    f32 _20;
    void* _21;
    void* _22;
    void* _23;
    u32 _24;
    DebugOperationParam* mDebugOperationParam;

    // 0x458
    // DebugOperationParam* mDebugOperationParam2;

    // 0x7b0
    // u8

    // 0x7b8
    // void*

    // 0x7c0
    // void*

    // 0x7c8
    // UserInstance* mUserInstance;

    // 0x7d0
    // u8
};
}  // namespace xlink2