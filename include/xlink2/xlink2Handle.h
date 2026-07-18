#pragma once

#include <basis/seadTypes.h>

#include "xlink2/xlink2Locator.h"
#include "xlink2/xlink2UserInstance.h"

namespace xlink2 {
class Event;

class Handle {
public:
    Handle() = default;
    Handle(Handle&) = delete;

    Handle(UserInstance* user_instance, const char* asset_key_name)
    {
        user_instance->searchAndEmitImpl(asset_key_name, this);
    }

    Handle(UserInstance* user_instance, const ResAssetCallTable& asset_ctb)
    {
        Locator locator {asset_ctb};
        user_instance->emitImpl(locator, this);
    }

    Handle(UserInstance* user_instance, const Locator& locator)
    {
        user_instance->emitImpl(locator, this);
    }

    Event* getEvent() { return static_cast<Event*>(mpResource); }
    s32 getCreateId() { return mCreateId; }

    void reset()
    {
        mpResource = nullptr;
        mCreateId = 0;
    }

    void setResource(void* resource) { mpResource = resource; }
    void setCreateId(s32 create_id) { mCreateId = create_id; }

private:
    void* mpResource = nullptr;
    s32 mCreateId = 0;
};
}  // namespace xlink2