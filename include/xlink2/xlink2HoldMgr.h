#pragma once

#include <container/seadObjList.h>
#include <hostio/seadHostIOReflexible.h>

#include "xlink2/xlink2Handle.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class UserInstance;

class HoldMgr : sead::hostio::Node {
public:
    HoldMgr(System*, sead::Heap*);
    virtual ~HoldMgr();

    struct HoldAssetInfo {
        Handle handle;
        UserInstance* userInstance;
        s32 _0;
        sead::ListNode listNode;
    };

    void calc();
    void fade(char const*, UserInstance*, int);
    void fade(UserInstance*, int);
    void fade(HoldAssetInfo*, int);
    void fadeAll();

    void genMessage(sead::hostio::Context*);

    u32 searchAndHold(char const*, Handle*, UserInstance*);

private:
    System* mSystem;
    sead::CriticalSection mCriticalSection;
    sead::ObjList<HoldAssetInfo> mHoldAssetInfoList;
    HoldAssetInfo mHoldAssetInfos[128];
    u8 _0;
};
}  // namespace xlink2