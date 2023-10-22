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

namespace aal {
class Emitter;
class IAssetInfoReadable;
}

namespace xlink2 {
class UserInstanceSLink : public UserInstance {

public:
    class CreateArgSLink {
    public:
        CreateArgSLink(char const*, IUser*);
        explicit CreateArgSLink(UserInstance::CreateArg const&);
        CreateArgSLink(CreateArgSLink const&);

    private:
    };

    class AssetLimiter {

    public:
        ~AssetLimiter() = default;
        AssetLimiter(s32, sead::Heap*);

        void clear();
        void append(Event const&, ResourceAccessorSLink const&, User*);

        void limit();
        void initialize(s32, char const*, ArrangeGroupParam const&);

    private:
    };

    ~UserInstanceSLink() override = default;
    UserInstanceSLink(CreateArgSLink const&, System*, User*, sead::Heap*);

    void allocEmitter(sead::Heap*);

    void searchAndEmit(char const*);
    void searchAndEmit(char const*, HandleSLink*);

    void emit(Locator const&);
    void emit(Locator const&, HandleSLink*);
    void emit(ResAssetCallTable const&);
    void emit(ResAssetCallTable const&, HandleSLink*);

    void searchAndHold(char const*);
    void searchAndHold(char const*, HandleSLink*);

    void stopAllEvent(s32);

    void fadeIfLoopSound();

    void setAssetInfoReader(aal::IAssetInfoReadable*);

    s32 getSoundSourceNum() const;
    u64 getResourceAccessor() const;
    ResourceAccessorSLink* getResourceSLink() const;

    void setupEmitter(ResAssetCallTable const&);

    void onPostCalc_() override;
    void onDestroy_() override;

    void freeEmitter_(aal::Emitter*);

    UserInstanceParam* allocInstanceParam_(sead::Heap*) override;
    void freeInstanceParam_(UserInstanceParam*, ResMode) override;
    void onSetupInstanceParam_(ResMode, sead::Heap*) override;

    void initModelAssetConnection_(ResMode, ParamDefineTable const*, sead::Heap*) override;

    bool doEventActivatingCallback_(Locator const&) override;
    void doEventActivatedCallback_(Locator const&, Event*) override;


    void makeDebugStringEvent(sead::BufferedSafeString*, sead::SafeString const&) const override;

private:
    sead::Heap* mHeap;
    void* mEmitter;
    u8 _6;
    void* mAssetInfoReader;
    IEventCallbackSLink* mEventCallback;
    sead::SafeArray<AssetLimiter*, 2> mAssetLimiters;
};
static_assert(sizeof(UserInstanceSLink) == 0x128, "Wrong size for 'xlink2::UserInstanceSLink'");

}  // namespace xlink2