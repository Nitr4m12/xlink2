#include <cstring>
#include "basis/seadTypes.h"

#include "xlink2/xlink2ToolConnectionContext.h"

namespace xlink2 {
void ToolConnectionContext::addLabel(const char* label)
{
    s32 len = strlen(label);
    memcpy(mLabel, label, len);
    mLabel[len] = '\0';
    mLabel = mLabel + len + 1;
}
}