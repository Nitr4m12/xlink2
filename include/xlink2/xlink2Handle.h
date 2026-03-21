#pragma once

#include <basis/seadTypes.h>

namespace xlink2 {
class Event;

class Handle {
public:
    Handle() = default;

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