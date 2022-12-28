#pragma once

#include "xlink2/xlink2.h"

namespace xlink2 {
class User;
class Error {
public:
    class Type;

private:
};

class ErrorMgr {
    virtual ~ErrorMgr();

public:
    ErrorMgr(System const*);

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