#include "xlink2/xlink2IEventCallbackELink.h"

namespace xlink2 {
void IEventCallbackELink::eventCreate(const EventArg& /*unused*/) {}
void IEventCallbackELink::eventDestroy(const EventArg& /*unused*/) {}
void IEventCallbackELink::eventActivated(const EventArg& /*unused*/) {}

u32 IEventCallbackELink::effectPreEmit(const EventArg& /*unused*/) {
    return 0;
}

void IEventCallbackELink::replaceResEset(ResEset* /*unused*/, const ResAssetCallTable& /*unused*/,
                                      const ResourceAccessorELink& /*unused*/,
                                      const char* /*unused*/) {}

void IEventCallbackELink::drawDebugInformation(sead::TextWriter* /*unused*/) {}
void IEventCallbackELink::drawEsetDebugInformation(sead::BufferedSafeString* /*unused*/,
                                                   sead::ptcl::EmitterSet* /*unused*/) {}

void IEventCallbackELink::effectEmited(const EventArg& /*unused*/) {}
void IEventCallbackELink::eventDeleted(const EventArg& /*unused*/) {}
void IEventCallbackELink::colorApplied(const EventArg& /*unused*/) {}
void IEventCallbackELink::eventCalced(const EventArg& /*unused*/) {}
}  // namespace xlink2