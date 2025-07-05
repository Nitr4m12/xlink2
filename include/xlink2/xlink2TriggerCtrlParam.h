#pragma once

#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>

namespace xlink2 {
struct ModelTriggerConnection;
class ActionTriggerCtrl;
class PropertyTriggerCtrl;
class AlwaysTriggerCtrl;
class TriggerCtrl;

struct TriggerCtrlParam {
    sead::Buffer<ModelTriggerConnection> _0x0;
    sead::Buffer<ModelTriggerConnection> _0x10;
    sead::Buffer<ModelTriggerConnection> _0x20;
    sead::Buffer<ActionTriggerCtrl*> actionTriggerCtrlBuffer;
    sead::Buffer<PropertyTriggerCtrl*> localPropertyTriggerCtrlBuffer;
    sead::Buffer<PropertyTriggerCtrl*> globalPropertyTriggerCtrlBuffer;
    AlwaysTriggerCtrl* alwaysTriggerCtrl;
    sead::PtrArray<TriggerCtrl> allTriggerCtrls;
};
static_assert(sizeof(TriggerCtrlParam) == 0x78, "xlink::TriggerCtrlParam size mismatch");

}  // namespace xlink2