#pragma once

#include "xlink2/xlink2Error.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2User.h"

namespace xlink2 {
class User;
class ErrorMgr {
    virtual ~ErrorMgr();

public:
    explicit ErrorMgr(System const*);

    void add(Error::Type, User const*, char const*);
    void calc();
    void clear(User const*);
    void clearAll();

    //void draw(sead::TextWriter*) const;

    void* getIsDebugBreakEnablePtr();

    bool shouldErrorNoticed(Error const*);
    bool shouldErrorNoticed(Error::Type const*);
private:
};
}  // namespace xlink2