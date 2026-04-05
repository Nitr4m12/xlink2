#include "xlink2/xlink2IUser.h"

namespace xlink2 {
const char* IUser::getActionSlotName([[maybe_unused]] s32 action_slot_idx) const
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

const char* IUser::getUserInformation() const
{
    return nullptr;
}

void IUser::getReservedAssetName([[maybe_unused]] ToolConnectionContext* ctx) const {}

u32 IUser::getNumAction([[maybe_unused]] s32) const
{
    return 0;
}

char* IUser::getActionName([[maybe_unused]] s32, [[maybe_unused]] s32) const
{
    return nullptr;
}

sead::Matrix34f IUser::getMtxCorrectingDrawBone() const
{
    return sead::Matrix34f::ident;
}
}  // namespace xlink2