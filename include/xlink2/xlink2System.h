#pragma once

#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <gfx/seadCamera.h>
#include <gfx/seadDrawContext.h>
#include <gfx/seadTextWriter.h>
#include <heap/seadHeap.h>
#include <hostio/seadHostIONode.h>

#include <xlink2/xlink2ErrorMgr.h>
#include "xlink2/xlink2DebugOperationParam.h"
#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2Resource.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class AssetExecutor;
class EditorBuffer;
class Event;
class HoldMgr;
class ILockProxy;
class IUser;
class ParamDefineTable;
class PropertyDefinition;
class ResourceBuffer;
struct ResUserHeader;
class UserResource;

class System : sead::hostio::Node {
public:
    void drawInformationEmitter(UserInstance*, sead::DrawContext*, sead::TextWriter*,
                                const sead::Camera&, const sead::Projection&,
                                const sead::Viewport&) const;

    System();

    void initSystem_(sead::Heap*, sead::Heap*, u32);
    void calc();

    User* searchUser(const char*, sead::Heap*, u32) const;
    s32 searchUserIgnoreHeap(const char*, User**, s32) const;

    virtual void drawInformation(sead::DrawContext*, sead::TextWriter*) const;
    virtual void drawInformation3D(sead::DrawContext*, const sead::Camera&, const sead::Projection&,
                                   const sead::Viewport&, f32) const;

    void makeDebugStringGlobalProperty(sead::BufferedSafeString*, const sead::SafeString&) const;

    s32 loadResource(void*);

    ResUserHeader* getResUserHeader(const char*);

    void removeUserInstance(UserInstance*);
    void unfixDrawInst_(UserInstance*);

    void unregistUserForGlobalPropertyTrigger_(User*);

    void allocGlobalProperty(u32, sead::Heap*);
    void createGlobalPropertyDefinitionTable(u32, const PropertyDefinition**, sead::Heap*);
    void setGlobalPropertyDefinition(u32, const PropertyDefinition*);
    void fixGlobalPropertyDefinition();
    void freeGlobalProperty();

    void addError(Error::Type /*unused*/, const User* /*unused*/, const char* /*unused*/, ...);

    void setGlobalPropertyValue(u32, s32);
    void setGlobalPropertyValue(u32, f32);
    s32 searchGlobalPropertyIndex(const char*) const;

    s32 incrementEventCreateId_();
    const Event* allocEvent();
    void freeEvent(Event*, sead::OffsetList<Event>*);
    void freeAllEvent(sead::OffsetList<Event>*);

    void registUserForGlobalPropertyTrigger(User*);
    void updateUserForGlobalPropertyTrigger(User*);

    const ParamDefineTable* getParamDefineTable() const;
    const ParamDefineTable* getParamDefineTable(ResMode) const;

    System* searchUserOrCreate_(const UserInstance::CreateArg&, sead::Heap*, u32);

    void drawInformationInstance3D_(UserInstance*, sead::DrawContext*, sead::TextWriter*) const;

    void drawInformationInstance3D_(UserInstance*, sead::DrawContext*, sead::TextWriter*,
                                   const sead::Camera&, const sead::Projection&,
                                   const sead::Viewport&) const;

    void drawText3D_(const sead::Matrix34f&, const sead::Vector2f&, const sead::SafeString&,
                    const sead::SafeString&, sead::TextWriter*, IUser*) const;
    void drawText3D_(const sead::Matrix34f&, const sead::Vector2f&, const sead::SafeString&,
                    const sead::SafeString&, sead::TextWriter*, const sead::Camera&,
                    const sead::Projection&, const sead::Viewport&) const;

    void writeBlinkText_(const sead::SafeString&, sead::TextWriter*) const;
    void writeLines_(const sead::SafeString&, sead::TextWriter*) const;

    bool isDrawTargetInstance_(UserInstance*) const;
    void updateDebugDrawUserList_() const;
    f32 calcDebugDrawSortKeyThreshold_() const;

    void clearError(const User*);

    void* getAnyone();

    void updateContainerCount(ContainerType, s32);

    void freeAssetExecutor(AssetExecutor*);

    void setErrorDispFrame(s32);

    void killAll();
    void killAllOneTimeEvent();

    bool isServerConnecting() const;

    void changeDebugOperationType(bool);

    void dumpActiveEvents() const;
    void dumpUsers() const;

    void requestSendPickedUserName(const sead::SafeString& /*unused*/);

    void resetOtameshiRequest();

    class DrawerModule {
    public:
        void begin(const sead::Camera&, const sead::Projection&);

        void setModelMatrix(const sead::Matrix34f&);
        void drawAxis(const sead::Vector3f&, f32);

        void end();
    };

    sead::Heap* getUserHeap() { return mUserCreateHeap; }
    EditorBuffer* getEditorBuffer() { return mEditorBuffer; }
    sead::Heap* getPrimaryHeap() { return mPrimaryHeap; }
    sead::Heap* getContainerHeap() { return mContainerHeap; }

    const DebugOperationParam& debugOperationParamOR() const { return mDebugOperationParamOR; }
    DebugOperationParam* debugOperationParamEditor() { return &mDebugOperationParamEditor; }

    bool isCallEnabled() const { return mIsCallEnabled; }

    ResourceBuffer* getResourceBuffer() { return mResourceBuffer; }

    sead::Random* getRandom() { return &mRandom; }

    bool isGlobalPropFixed() { return mIsGlobalPropFixed; }

    const PropertyDefinition* getPropertyDefinition(u32 idx) const { return mGlobalPropertyDefinitions[idx]; }

    virtual void createUserResource(User*, sead::Heap*) = 0;
    virtual void allocHandle(sead::Heap*) = 0;
    virtual u32 getUserParamNum() const = 0;
    virtual sead::SafeString* getModuleName() const = 0;
    virtual void allocAssetExecutor(Event*) = 0;
    virtual ILockProxy* getModuleLockObj() const = 0;
    virtual u32 getResourceVersion() const = 0;

    virtual ~System();

    virtual Event* getEventFromPool_(u32) const = 0;
    virtual void preDrawInformation_(sead::TextWriter*) const;
    virtual void postDrawInformation_(sead::TextWriter*) const;
    virtual void drawInformationSystemDetail_(sead::TextWriter*) const = 0;
    virtual void drawInformationEvent_(sead::TextWriter*) const = 0;

protected:
    const DebugOperationParam& getDebugOperationParam() { return mIsOperationOREnabled ? mDebugOperationParamOR : mDebugOperationParamEditor; }

    struct OtameshiRequest;

    ResourceBuffer* mResourceBuffer {};
    sead::OffsetList<User> mUserList;
    s32 _0x28 {};
    u32 mMaxNumEventPool {};
    u32 mNumEventPool {};
    s32 mEventCreateId {1};
    bool _0x38 {};
    u32 mNumGlobalProperty {};
    const PropertyDefinition** mGlobalPropertyDefinitions {};
    PropertyValueType* mGlobalPropertyValues {};
    sead::BitFlag64 mGlobalPropertyBitfield;
    bool mIsGlobalPropFixed {};
    ErrorMgr* mErrorMgr {};
    HoldMgr* mHoldMgr {};
    s32 _0x70 {-1};
    bool mIsCallEnabled {true};
    sead::Heap* mUserCreateHeap {};
    f32 _0x80 {1.0f};
    sead::PtrArray<User> mGlobalPropertyTriggerUserList;
    sead::Random mRandom;
    sead::Heap* mContainerHeap;
    sead::Heap* mAssetExecutorHeap;
    sead::Heap* mPrimaryHeap {};
    EditorBuffer* mEditorBuffer {};
    s32 mTick {};
    f32 _0xcc {1.0f};
    sead::OffsetList<User>* mDebugDrawUserList {};
    f32 mUserSortKey {-1.0f};
    sead::SafeString* mDebugString {};
    sead::PtrArray<char> mDebugUserNameList;
    s32 _0xf8 {-1};
    DebugOperationParam mDebugOperationParamOR;
    DebugOperationParam mDebugOperationParamEditor;
    bool mIsOperationOREnabled {true};
    sead::Buffer<OtameshiRequest> mOtameshiBuffer;
    UserInstance* mDrawInstance {};
    bool mShowAalInfo {};
};
static_assert(sizeof(System) == 0x7d8, "xlink2::System size mismatch");

}  // namespace xlink2