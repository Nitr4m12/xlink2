#pragma once

#include <thread/seadMutex.h>
#include <thread/seadSpinLock.h>

namespace xlink2 {

struct Handle {
    void* _0 = nullptr;
    int _8 = 0;
};

struct ResourceHeader {
    u8 magic[4];
    u32 dataSize;
    u32 version;
    u32 numResParam;
    u32 numResAssetParam;
    u32 numResTriggerOverwriteParam;
    u32 triggerOverwriteParamTablePos;
    u32 localPropertyNameRefTablePos;
    u32 numLocalPropertyNameRefTable;
    u32 numLocalPropertyEnumNameRefTable;
    u32 numDirectValueTable;
    u32 numRandomTable;
    u32 numCurveTable;
    u32 numCurvePointTable;
    u32 exRegionPos;
    u32 numUser;
    u32 conditionTablePos;
    u32 nameTablePos;
};

class BoneMtx;
class DebugLogFlag;
class DebugOperationParam;
class EditorHeader;
class ELinkAssetParamId;
class ELinkEventParam;

class F32PropertyDefinition;
template <typename T>
class FixedEnumPropertyDefinition;

namespace IEventCallbackELink {};
namespace IEventCallbackSLink {};

class ModelTriggerConnection;

class ParamValueType;

class PropertyDefinition;
class PtclResourceAccessorELink {
    // public:
    // void* searchEmitterSetID(sead::ptcl::PtclSystem*, char const*, s32&, s32&);
};
class RandomContainer {
public:
    ~RandomContainer();
    void calc();
    bool start();

private:
};
class RandomContainer2 {
    ~RandomContainer2();
    void* start();
};
class ResAction;
class ResActionSlot;
class ResActionTrigger;
class ResAssetCallTable;
class ResContainerParam;
class ResCurveCallTable;
class ResMode;
class ResParam;
class ResProperty;
class ResRandomCallTable;
class ResTriggerOverwriteParam;

class S32PropertyDefinition;
class SequenceContainer;
class SwitchContainter;
class System;
class SystemELink;
class SystemSLink;
class ToolConnectionContext;
class TriggerCtrl;
class TriggerCtrlMgr;
class TriggerLocator;
class TriggerType;
class User;
class UserInstance;
class UserInstanceELink;
class UserInstanceSLink;
class UserResource;
class UserResourceELink;
class UserResourceSLink;

class ValueReferenceType;
}  // namespace xlink2
