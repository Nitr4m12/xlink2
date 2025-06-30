#include <xlink2/xlink2ErrorMgr.h>
#include "prim/seadScopedLock.h"

namespace xlink2 {
void ErrorMgr::add(Error::Type, const User*, const char*) {}
void ErrorMgr::clear(const User*) {}
void ErrorMgr::clearAll() 
{
    if (mIsNotThrown) 
    {
        mCriticalSection.lock();
        mErrorEntries[0].type = Error::Type::None;
        mErrorEntries[1].type = Error::Type::None;
        mErrorEntries[2].type = Error::Type::None;
        mErrorEntries[3].type = Error::Type::None;
        mErrorEntries[4].type = Error::Type::None;
        mErrorEntries[5].type = Error::Type::None;
        mErrorEntries[6].type = Error::Type::None;
        mErrorEntries[7].type = Error::Type::None;
        mErrorEntries[8].type = Error::Type::None;
        mErrorEntries[9].type = Error::Type::None;
        mErrorEntries[10].type = Error::Type::None;
        mErrorEntries[11].type = Error::Type::None;
        mErrorEntries[12].type = Error::Type::None;
        mErrorEntries[13].type = Error::Type::None;
        mErrorEntries[14].type = Error::Type::None;
        mErrorEntries[15].type = Error::Type::None;
        mErrorEntries[16].type = Error::Type::None;
        mErrorEntries[17].type = Error::Type::None;
        mErrorEntries[18].type = Error::Type::None;
        mErrorEntries[19].type = Error::Type::None;
        mErrorEntries[20].type = Error::Type::None;
        mErrorEntries[21].type = Error::Type::None;
        mErrorEntries[22].type = Error::Type::None;
        mErrorEntries[23].type = Error::Type::None;
        mErrorEntries[24].type = Error::Type::None;
        mErrorEntries[25].type = Error::Type::None;
        mErrorEntries[26].type = Error::Type::None;
        mErrorEntries[27].type = Error::Type::None;
        mErrorEntries[28].type = Error::Type::None;
        mErrorEntries[29].type = Error::Type::None;
        mErrorEntries[30].type = Error::Type::None;
        mErrorEntries[31].type = Error::Type::None;
        mCriticalSection.unlock();
    }
}
void ErrorMgr::calc() {}
}