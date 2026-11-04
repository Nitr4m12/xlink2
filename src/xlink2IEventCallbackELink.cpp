#include "xlink2/xlink2IEventCallbackELink.h"

namespace xlink2 {
void IEventCallbackELink::eventCreate([[maybe_unused]] const EventArg& arg) {}
void IEventCallbackELink::eventDestroy([[maybe_unused]] const EventArg& arg) {}
void IEventCallbackELink::eventActivated([[maybe_unused]] const EventArg& arg) {}

u32 IEventCallbackELink::effectPreEmit([[maybe_unused]] const EventArg& arg)
{
    return 0;
}

void IEventCallbackELink::replaceResEset([[maybe_unused]] ResEset* res_eset,
                                         [[maybe_unused]] const ResAssetCallTable& asset_ctb,
                                         [[maybe_unused]] const ResourceAccessorELink& accessor,
                                         [[maybe_unused]] const char* eset_name)
{
}

void IEventCallbackELink::drawDebugInformation([[maybe_unused]] sead::TextWriter* text_writer) {}
void IEventCallbackELink::drawEsetDebugInformation(
    [[maybe_unused]] sead::BufferedSafeString* debug_string,
    [[maybe_unused]] sead::ptcl::EmitterSet* emitter_set)
{
}

void IEventCallbackELink::effectEmited([[maybe_unused]] const EventArg& arg) {}
void IEventCallbackELink::eventDeleted([[maybe_unused]] const EventArg& arg) {}
void IEventCallbackELink::colorApplied([[maybe_unused]] const EventArg& arg) {}
void IEventCallbackELink::eventCalced([[maybe_unused]] const EventArg& arg) {}
}  // namespace xlink2