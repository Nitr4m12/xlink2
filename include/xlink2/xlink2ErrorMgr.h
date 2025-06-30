#pragma once

#include <gfx/seadTextWriter.h>

#include "xlink2/xlink2Error.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2User.h"

namespace xlink2 {
class User;
class ErrorMgr {

public:
    explicit ErrorMgr(System const*);
    ~ErrorMgr();

    void add(Error::Type, User const*, char const*);
    void clear(User const*);
    void clearAll();
    void calc();

    void draw(sead::TextWriter*) const;

    bool shouldErrorNoticed_(Error const*);
    bool shouldErrorNoticed_(Error::Type const*);

    void* getIsDebugBreakEnablePtr();

private:
    bool mIsNotThrown;
    Error mErrorEntries[32];
    u32 mErrorDispFrame;
    u32 _2;
    void* _3;
    System* mSystem;
    u8 p[0xb0];
    sead::CriticalSection mCriticalSection;
};
static_assert(sizeof(ErrorMgr) == 0x5110, "xlink2::ErrorMgr size mismatch");

}  // namespace xlink2