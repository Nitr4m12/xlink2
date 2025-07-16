#pragma once

#include <gfx/seadTextWriter.h>
#include <thread/seadCriticalSection.h>

#include "xlink2/xlink2Error.h"

namespace xlink2 {
class System;
class User;

class ErrorMgr {
public:
    explicit ErrorMgr(const System*);
    ~ErrorMgr() = default;

    void add(Error::Type, const User*, const char*);
    void clear(const User*);
    void clearAll();
    void calc();

    void draw(sead::TextWriter*) const;

    bool shouldErrorNoticed_(const Error*);
    bool shouldErrorNoticed_(const Error::Type*);

    void* getIsDebugBreakEnablePtr();

    s32 getDispFrame() { return mDispFrame; }
    void setDispFrame(s32 frame) { mDispFrame = frame; }

    const sead::CriticalSection* getCriticalSection() const { return &mCriticalSection; }

private:
    bool mIsNotThrown;
    Error mErrorEntries[32];
    s32 mDispFrame;
    u32 _2;
    void* _3;
    System* mSystem;
    u8 p[0xb0];
    sead::CriticalSection mCriticalSection;
};
static_assert(sizeof(ErrorMgr) == 0x5110, "xlink2::ErrorMgr size mismatch");

}  // namespace xlink2