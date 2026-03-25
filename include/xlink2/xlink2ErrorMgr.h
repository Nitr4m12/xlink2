#pragma once

#include <gfx/seadTextWriter.h>
#include <thread/seadCriticalSection.h>

#include "xlink2/xlink2Error.h"

namespace xlink2 {
class System;
class User;

static bool mIsDebugBreakEnable;

class ErrorMgr {
public:
    explicit ErrorMgr(const System*);
    ~ErrorMgr() = default;

    void add([[maybe_unused]] Error::Type, [[maybe_unused]] const User*, [[maybe_unused]] const char*);
    void clear([[maybe_unused]] const User*);
    void clearAll();
    void calc();

    void draw(sead::TextWriter*) const;

    bool shouldErrorNoticed_(const Error*);
    bool shouldErrorNoticed_(const Error::Type*);

    bool* getIsDebugBreakEnablePtr();

    s32 getDispFrame() { return mDispFrame; }
    void setDispFrame(s32 frame) { mDispFrame = frame; }

    const sead::CriticalSection* getCriticalSection() const { return &mCriticalSection; }

private:
    bool mIsNotThrown {true};
    Error mErrorEntries[32] {};
    s32 mDispFrame {0};
    // u32 _2 {};
    void* _3 {};
    const System* mSystem {};
    u32 _4[42];
    u32 _5 {0};
    sead::CriticalSection mCriticalSection;
};
static_assert(sizeof(ErrorMgr) == 0x5110, "xlink2::ErrorMgr size mismatch");
}  // namespace xlink2