#include "xlink2/xlink2IUser.h"

namespace xlink2 {
char* IUser::getActionSlotName(int) const
{
    return nullptr;
}

void* IUser::getDebugDrawCamera() const
{
    return nullptr;
}

void* IUser::getDebugDrawProjection() const
{
    return nullptr;
}

char* IUser::getDebugUserName() const
{
    return nullptr;
}

void* IUser::getUserInformation() const
{
    return nullptr;
}

void IUser::getReservedAssetName(ToolConnectionContext*) const {}

u32 IUser::getNumAction(int) const
{
    return 0;
}

char* IUser::getActionName(int, int) const
{
    return nullptr;
}

}  // namespace xlink2