#include <xlink2/xlink2ErrorMgr.h>

namespace xlink2 {
ErrorMgr::ErrorMgr(const System* system)
    : mSystem(system)
{
    for (s32 i {0}; i < 42; ++i)
        _4[i] = 2;
}

void ErrorMgr::add([[maybe_unused]] Error::Type type, 
                   [[maybe_unused]] const User* user, 
                   [[maybe_unused]] const char* msg) 
{
#ifdef SEAD_DEBUG
#endif
}

void ErrorMgr::clear([[maybe_unused]] const User* user) 
{
#ifdef SEAD_DEBUG
#endif
}

void ErrorMgr::clearAll() 
{
    if (mIsNotThrown) 
    {
        mCriticalSection.lock();
        for (s32 i {0}; i < 32; ++i)
            mErrorEntries[i].type = Error::Type::None;
        mCriticalSection.unlock();
    }
}

void ErrorMgr::calc() 
{
#ifdef SEAD_DEBUG
#endif
}

bool* ErrorMgr::getIsDebugBreakEnablePtr()
{
    return &mIsDebugBreakEnable;
}
} // namespace xlink2