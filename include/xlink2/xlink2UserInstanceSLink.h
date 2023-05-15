#pragma once

#include "basis/seadTypes.h"
#include "heap/seadHeap.h"
#include "xlink2/xlink2ArrangeGroupParam.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2HandleSLink.h"
#include "xlink2/xlink2IEventCallbackSLink.h"
#include "xlink2/xlink2IUser.h"
#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResMode.h"
#include "xlink2/xlink2ResourceAccessorSLink.h"

namespace xlink2 {
class UserInstanceSLink : public UserInstance {
    ~UserInstanceSLink() override;

public:
    class AssetLimiter {
        virtual ~AssetLimiter();

    public:
        AssetLimiter(s32, sead::Heap*);
        void initialize(s32, char const*, ArrangeGroupParam const&);

        void append(Event const&, ResourceAccessorSLink const&, User*);
        void clear();
        void limit();

    private:
    };
    class CreateArgSLink {
    public:
        CreateArgSLink(char const*, IUser*);
        explicit CreateArgSLink(UserInstance::CreateArg const&);
        CreateArgSLink(CreateArgSLink const&);

    private:
    };
    UserInstanceSLink(CreateArgSLink const&, System*, User*, sead::Heap*);

    void allocEmitter(sead::Heap*);
    UserInstanceParam* allocInstanceParam_(sead::Heap*) override;
    void doEventActivatedCallback_(Locator const&, Event*) override;
    bool doEventActivatingCallback_(Locator const&) override;

    void emit(Locator const&);
    void emit(Locator const&, HandleSLink*);
    void emit(ResAssetCallTable const&);
    void emit(ResAssetCallTable const&, HandleSLink*);

    void fadeIfLoopSound();
    // void freeEmitter(aal::Emitter*)
    void freeInstanceParam_(UserInstanceParam*, ResMode) override;

    u64 getResourceAccessor() const;
    ResourceAccessorSLink* getResourceSLink() const;
    s32 getSoundSourceNum() const;

    void initModelAssetConnection_(ResMode, ParamDefineTable const*, sead::Heap*) override;

    void makeDebugStringEvent(sead::BufferedSafeString*, sead::SafeString const&) const override;

    void onDestroy_() override;
    void onPostCalc_() override;
    void onSetupInstanceParam_(ResMode, sead::Heap*) override;

    void searchAndEmit(char const*);
    void searchAndEmit(char const*, HandleSLink*);
    void searchAndHold(char const*);
    void searchAndHold(char const*, HandleSLink*);

    // void setAssetInfoReader(aal::IAssetInfoReadable*);

    void setupEmitter(ResAssetCallTable const&);
    void stopAllEvent(s32);

private:
    sead::Heap* mHeap;
    void* mEmitter;
    u8 _6;
    void* mAssetInfoReader;
    IEventCallbackSLink* mEventCallback;
    sead::SafeArray<AssetLimiter*, 2> mAssetLimiters;
};
}  // namespace xlink2