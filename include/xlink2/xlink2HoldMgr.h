#pragma once

#include "hostio/seadHostIOReflexible.h"

#include "xlink2/xlink2Handle.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class HoldMgr {
    virtual ~HoldMgr();

public:
    HoldMgr(System*, sead::Heap*);

    class HoldAssetInfo;

    void calc();
    void fade(char const*, UserInstance*, int);
    void fade(UserInstance*, int);
    void fade(HoldAssetInfo*, int);
    void fadeAll();

    void genMessage(sead::hostio::Context*);

    u32 searchAndHold(char const*, Handle*, UserInstance*);

private:
};
}  // namespace xlink2