#include <cstdarg>

#include "xlink2/xlink2ResourceAccessor.h"
#include "math/seadMathCalcCommon.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
ResourceAccessor::~ResourceAccessor() = default;

const ResAssetCallTable* ResourceAccessor::searchCallTable(const char* name) const
{
    if (mpUserResource && mpSystem->isCallEnabled()) {
        UserResourceParam* param = mpUserResource->getParam();

        if (param && param->isSetup)
            return mpUserResource->searchAssetCallTableByName(name);
    }

    return nullptr;
}

void ResourceAccessor::searchCallTable(Locator* locator, const char* name) const
{
    if (mpUserResource && mpSystem->isCallEnabled()) {
        UserResourceParam* param = mpUserResource->getParam();

        if (param && param->isSetup)
            mpUserResource->searchAssetCallTableByName(locator, name);
    }
}

const ResAssetCallTable* ResourceAccessor::getCallTable(u32 idx) const
{
    if (mpUserResource && mpSystem->isCallEnabled()) {
        UserResourceParam* param = mpUserResource->getParam();

        if (param && param->isSetup) {
            if (idx < mpUserHeader->numCallTable)
                return mpUserResource->getAssetCallTableItem(idx);

            setError_("getCallTable: idx(%d) >= numCallTable(%d)", idx, mpUserHeader->numCallTable);
        }
    }

    return nullptr;
}

void ResourceAccessor::setError_(const char* fmt, ...) const
{
    va_list args;
    va_start(args, fmt);
    sead::FixedSafeString<256> msg;
    msg.formatV(fmt, args);
    va_end(args);
    User* user {nullptr};
    System* sys {mpSystem};
    if (mpUserResource != nullptr)
        user = mpUserResource->getUser();

    sys->addError(Error::Type::ResourceAccessFailed, user, "%s", msg.getBuffer());
}

const char* ResourceAccessor::getKeyName(const ResAssetCallTable& asset_ctb) const
{
    return calcOffset<const char>(asset_ctb.keyNamePos);
}

// NON-MATCHING: Wrong register
ContainerType ResourceAccessor::getCallTableType(const ResAssetCallTable& asset_ctb) const
{
    if (!isContainer(asset_ctb))
        return ContainerType::Asset;

    ResContainerParam* container_param {calcOffset<ResContainerParam>(asset_ctb.paramStartPos)};
    if (container_param != nullptr) {
        if (container_param->type > ContainerType::Sequence) {
            setError_("[%s] invalid container type(=%d)", getKeyName(asset_ctb), container_param->type);
            return ContainerType::Asset;
        }
        return container_param->type;
    }

    return ContainerType::Asset;
}

const ContainerBase* ResourceAccessor::getContainer(const ResAssetCallTable& asset_ctb) const
{
    if (isContainer(asset_ctb))
        return calcOffset<ContainerBase>(asset_ctb.paramStartPos);
    return nullptr;
}

// WIP
const sead::SafeString* ResourceAccessor::getCallTableTypeName(const ResAssetCallTable& asset_ctb) const 
{
    if (isContainer(asset_ctb)) {
        ResContainerParam* container_param {calcOffset<ResContainerParam>(asset_ctb.paramStartPos)};
        if (container_param != nullptr) {
            if (container_param->type > ContainerType::Sequence) {
                setError_("[%s] invalid container type(=%d)", getKeyName(asset_ctb));
                return &sContainerNames[6];
            }
            return &sContainerNames[(s8)container_param->type];

        }
    }

    return &sContainerNames[5];
}

bool ResourceAccessor::isContainer(const ResAssetCallTable& asset_ctb) const
{
    return asset_ctb.flag.isOnBit(0);
}

const char* ResourceAccessor::getCustomParamValueString(u32 idx,
                                                        const ResAssetCallTable& asset_ctb) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    u32 id = param_define_table->getNumCustomParam() + idx;

    if (id < param_define_table->getNumAssetParam()) {
        if (param_define_table->getAssetParamType(id) == ParamValueType::String) {
            if (checkAndErrorIsAsset_(asset_ctb, "getCustomParamValueString(%d)", idx)) {
                auto* res_param = getResParamFromAssetParamPos(asset_ctb.paramStartPos, id);
                return res_param != nullptr ? getResParamValueString_(*res_param) : param_define_table->getAssetParamDefaultValueString(id);
            }
            return "";
        }
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();
        system->addError(Error::Type::CustomParamAccessFailed, user, " idx=%d is not string type", idx);
    }
    else {
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();

        system->addError(Error::Type::CustomParamAccessFailed, user, "customParamIdx[%d] is not found", idx);
    }

    return "";
}

const ResParam* ResourceAccessor::getResParamFromAssetParamPos(u32 param_start_pos, u32 idx) const
{
    auto* mask = calcOffset<sead::BitFlag64>(param_start_pos);
    if (mask->isOnBit(idx)) {
        s32 param_idx {mask->countRightOnBit(idx) - 1};
        return &reinterpret_cast<ResParam*>(mask + 1)[param_idx];
    }

    return nullptr;
}

bool ResourceAccessor::checkAndErrorIsAsset_(const ResAssetCallTable& asset_ctb,
                                             const char* fmt, ...) const
{
    if (asset_ctb.flag & 1) {
        va_list args;
        va_start(args, fmt);
        sead::FixedSafeString<256> msg;
        msg.formatV(fmt, args);
        va_end(args);
        User* user {nullptr};
        System* sys {mpSystem};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();

        sys->addError(Error::Type::ResourceAccessFailed, user, "%s: [%s] is container", msg.getBuffer(), getKeyName(asset_ctb));
        return false;
    }
    return true;
}

const char* ResourceAccessor::getResParamValueString_(const ResParam& param) const
{
    UserResourceParam* user_param = mpUserResource->getParam();
    u64 value_string_pos =
        user_param->commonResourceParam->nameTablePos + (param.getValue());
    return calcOffset<char>(value_string_pos);
}

bool ResourceAccessor::getCustomParamValueBool(u32 idx, const ResAssetCallTable& asset_ctb) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    u32 id = idx + param_define_table->getNumCustomParam();

    if (id < param_define_table->getNumAssetParam()) {
        ParamValueType param_type {param_define_table->getAssetParamType(id)};
        if (param_type == ParamValueType::Bool) {
            bool is_asset {checkAndErrorIsAsset_(asset_ctb, "getCustomParamValueBool(%d)", idx)};
            if (is_asset) {
                auto* res_param = getResParamFromAssetParamPos(asset_ctb.paramStartPos, id);
                return res_param != nullptr ? getResParamValueInt_(*res_param) : param_define_table->getAssetParamDefaultValueInt(id);
            }
            return false;
        }
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();
        system->addError(Error::Type::CustomParamAccessFailed, user, " idx=%d is not int type", idx);
    }
    else {
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();
        system->addError(Error::Type::CustomParamAccessFailed, user, "customParamIdx[%d] is not found", idx);
    }
    
    return false;
}

s32 ResourceAccessor::getResParamValueInt_(const ResParam& param) const
{
    UserResourceParam* user_resource_param {mpUserResource->getParam()};
    return user_resource_param->commonResourceParam->directValueTable[param.getValue()];
}

s32 ResourceAccessor::getCustomParamValueInt(u32 idx, const ResAssetCallTable& asset_ctb) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    u32 id = idx + param_define_table->getNumCustomParam();

    if (id < param_define_table->getNumAssetParam()) {
        ParamValueType param_type {param_define_table->getAssetParamType(id)};
        if (param_type == ParamValueType::UInt32) {
            bool is_asset {checkAndErrorIsAsset_(asset_ctb, "getCustomParamValueInt(%d)", idx)};
            if (is_asset) {
                auto* res_param = getResParamFromAssetParamPos(asset_ctb.paramStartPos, id);
                return res_param != nullptr ? getResParamValueInt_(*res_param) : param_define_table->getAssetParamDefaultValueInt(id);
            }
            return false;
        }
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();
        system->addError(Error::Type::CustomParamAccessFailed, user, " idx=%d is not int type", idx);
    }
    else {
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();
        system->addError(Error::Type::CustomParamAccessFailed, user, "customParamIdx[%d] is not found", idx);
    }
    
    return false;
}

f32 ResourceAccessor::getCustomParamValueFloat(u32 idx, const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    u32 id = idx + param_define_table->getNumCustomParam();

    if (id < param_define_table->getNumAssetParam()) {
        ParamValueType param_type {param_define_table->getAssetParamType(id)};
        if (param_type == ParamValueType::Float) {
            bool is_asset {checkAndErrorIsAsset_(asset_ctb, "getCustomParamValueFloat(%d)", idx)};
            if (is_asset) {
                auto* res_param = getResParamFromAssetParamPos(asset_ctb.paramStartPos, id);
                return res_param != nullptr ? getResParamValueFloat_(*res_param, user_instance) : param_define_table->getAssetParamDefaultValueFloat(id);
            }
            return 0.0f;
        }
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();
        system->addError(Error::Type::CustomParamAccessFailed, user, " idx=%d is not float type", idx);
    }
    else {
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();
        system->addError(Error::Type::CustomParamAccessFailed, user, "customParamIdx[%d] is not found", idx);
    }
    
    return 0.0f;
}

// NON-MATCHING: missing instructions
f32 ResourceAccessor::getResParamValueFloat_(const ResParam& res_param, const UserInstance* user_instance) const
{
    switch (res_param.getRefType()) {
    case ValueReferenceType::Direct:
        return static_cast<f32>(getResParamValueInt_(res_param));
    
    case ValueReferenceType::Curve: {
        ResCurveCallTable* curve_ctb {mpUserResource->getParam()->commonResourceParam->curveCallTable};
        if (&curve_ctb[res_param.getValue()] != nullptr)
            return getCurveValue(curve_ctb[res_param.getValue()], user_instance);
        break;
    }
    case ValueReferenceType::Random: {
        ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
        ResRandomCallTable* random_ctb_item {&random_ctb[res_param.getValue()]};
        if (random_ctb != nullptr && random_ctb_item != nullptr)
            return getRandomValue(*random_ctb_item);
        break;
    }
    case ValueReferenceType::Random2Pow: {
        ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
        ResRandomCallTable* random_ctb_item {&random_ctb[res_param.getValue()]};
        if (random_ctb != nullptr && random_ctb_item != nullptr)
            return getRandomValue(*random_ctb_item, 2.0f);
        break;
    }
    case ValueReferenceType::Random3Pow: {
        ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
        ResRandomCallTable* random_ctb_item {&random_ctb[res_param.getValue()]};
        if (random_ctb != nullptr && random_ctb_item != nullptr)
            return getRandomValue(*random_ctb_item, 3.0f);
        break;
    }
    case ValueReferenceType::Random4Pow: {
        ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
        ResRandomCallTable* random_ctb_item {&random_ctb[res_param.getValue()]};
        if (random_ctb != nullptr && random_ctb_item != nullptr)
            return getRandomValue(*random_ctb_item, 4.0f);
        break;
    }
    case ValueReferenceType::Random1Point5Pow: {
        ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
        ResRandomCallTable* random_ctb_item {&random_ctb[res_param.getValue()]};
        if (random_ctb != nullptr && random_ctb_item != nullptr)
            return getRandomValue(*random_ctb_item, 1.5f);
        break;
    }
    case ValueReferenceType::RandomWeightMin2Pow: {
        ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
        ResRandomCallTable* random_ctb_item {&random_ctb[res_param.getValue()]};
        if (random_ctb != nullptr && random_ctb_item != nullptr)
            return getRandomValueWeightMin(*random_ctb_item, 2.0f);
        break;
    }
    case ValueReferenceType::RandomWeightMin3Pow: {
        ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
        ResRandomCallTable* random_ctb_item {&random_ctb[res_param.getValue()]};
        if (random_ctb != nullptr && random_ctb_item != nullptr)
            return getRandomValueWeightMin(*random_ctb_item, 3.0f);
        break;
    }
    case ValueReferenceType::RandomWeightMin4Pow: {
        ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
        ResRandomCallTable* random_ctb_item {&random_ctb[res_param.getValue()]};
        if (random_ctb != nullptr && random_ctb_item != nullptr)
            return getRandomValueWeightMin(*random_ctb_item, 4.0f);
        break;
    }
    case ValueReferenceType::RandomWeightMin1Point5Pow: {
        ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
        ResRandomCallTable* random_ctb_item {&random_ctb[res_param.getValue()]};
        if (random_ctb != nullptr && random_ctb_item != nullptr)
            return getRandomValueWeightMin(*random_ctb_item, 1.5f);
        break;
    }
    case ValueReferenceType::RandomWeightMax2Pow: {
        ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
        ResRandomCallTable* random_ctb_item {&random_ctb[res_param.getValue()]};
        if (random_ctb != nullptr && random_ctb_item != nullptr)
            return getRandomValueWeightMax(*random_ctb_item, 2.0f);
        break;
    }
    case ValueReferenceType::RandomWeightMax3Pow: {
        ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
        ResRandomCallTable* random_ctb_item {&random_ctb[res_param.getValue()]};
        if (random_ctb != nullptr && random_ctb_item != nullptr)
            return getRandomValueWeightMax(*random_ctb_item, 3.0f);
        break;
    }
    case ValueReferenceType::RandomWeightMax4Pow: {
        ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
        ResRandomCallTable* random_ctb_item {&random_ctb[res_param.getValue()]};
        if (random_ctb != nullptr && random_ctb_item != nullptr)
            return getRandomValueWeightMax(*random_ctb_item, 4.0f);
        break;
    }
    case ValueReferenceType::RandomWeightMax1Point5Pow: {
        ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
        ResRandomCallTable* random_ctb_item {&random_ctb[res_param.getValue()]};
        if (random_ctb != nullptr && random_ctb_item != nullptr)
            return getRandomValueWeightMax(*random_ctb_item, 1.5f);
        break;
    }
    default:
        setError_("getFloat_: invalid referenceType(%d)", res_param.getRefType());
        break;
    }

    return 0.0f;
}

const char* ResourceAccessor::getCustomParamValueString(const char* name, const ResAssetCallTable& asset_ctb) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    s32 id = param_define_table->searchAssetParamIdxFromCustomParamName(name);

    if (id < 0) {
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();
        system->addError(Error::Type::CustomParamAccessFailed, user, "param[%s] is not found", name);
    }
    else {
        if (param_define_table->getAssetParamType(id) != ParamValueType::String) {
            System* system = mpSystem;
            User* user {};
            if (mpUserResource != nullptr)
                user = mpUserResource->getUser();

            system->addError(Error::Type::CustomParamAccessFailed, user, " param[%s] is not string type", name);
        }
        else {
            if (checkAndErrorIsAsset_(asset_ctb, "getCustomParamValueString(%s)", name)) {
                auto* res_param = getResParamFromAssetParamPos(asset_ctb.paramStartPos, id);
                return res_param != nullptr ? getResParamValueString_(*res_param) : param_define_table->getAssetParamDefaultValueString(id);
            }
            return "";
        }

    }

    return nullptr;
}

bool ResourceAccessor::getCustomParamValueBool(const char* name, const ResAssetCallTable& asset_ctb) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    s32 id = param_define_table->searchAssetParamIdxFromCustomParamName(name);

    if (id < 0) {
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();

        system->addError(Error::Type::CustomParamAccessFailed, user, "param[%s] is not found", name);
    }
    else {
        if (param_define_table->getAssetParamType(id) != ParamValueType::Bool) {
            System* system = mpSystem;
            User* user {};
            if (mpUserResource != nullptr)
                user = mpUserResource->getUser();

            system->addError(Error::Type::CustomParamAccessFailed, user, " param[%s] is not int type", name);
        }
        else {
            if (checkAndErrorIsAsset_(asset_ctb, "getCustomParamValueBool(%s)", name)) {
                auto* res_param = getResParamFromAssetParamPos(asset_ctb.paramStartPos, id);
                return res_param != nullptr ? getResParamValueInt_(*res_param) : param_define_table->getAssetParamDefaultValueInt(id);
            }
            return false;
        }

    }

    return false;
}

s32 ResourceAccessor::getCustomParamValueInt(const char* name, const ResAssetCallTable& asset_ctb) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    s32 id = param_define_table->searchAssetParamIdxFromCustomParamName(name);

    if (id < 0) {
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();

        system->addError(Error::Type::CustomParamAccessFailed, user, "param[%s] is not found", name);
    }
    else {
        if (param_define_table->getAssetParamType(id) != ParamValueType::UInt32) {
            System* system = mpSystem;
            User* user {};
            if (mpUserResource != nullptr)
                user = mpUserResource->getUser();

            system->addError(Error::Type::CustomParamAccessFailed, user, " param[%s] is not int type", name);
        }
        else {
            if (checkAndErrorIsAsset_(asset_ctb, "getCustomParamValueInt(%s)", name)) {
                auto* res_param = getResParamFromAssetParamPos(asset_ctb.paramStartPos, id);
                return res_param != nullptr ? getResParamValueInt_(*res_param) : param_define_table->getAssetParamDefaultValueInt(id);
            }
            return 0;
        }

    }

    return 0;
}

f32 ResourceAccessor::getCustomParamValueFloat(const char* name, const ResAssetCallTable& asset_ctb, const UserInstance* user_instance) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    s32 id = param_define_table->searchAssetParamIdxFromCustomParamName(name);

    if (id < 0) {
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();

        system->addError(Error::Type::CustomParamAccessFailed, user, "param[%s] is not found", name);
    }
    else {
        if (param_define_table->getAssetParamType(id) != ParamValueType::Float) {
            System* system = mpSystem;
            User* user {};
            if (mpUserResource != nullptr)
                user = mpUserResource->getUser();

            system->addError(Error::Type::CustomParamAccessFailed, user, " param[%s] is not float type", name);
        }
        else {
            if (checkAndErrorIsAsset_(asset_ctb, "getCustomParamValueFloat(%s)", name)) {
                auto* res_param = getResParamFromAssetParamPos(asset_ctb.paramStartPos, id);
                return res_param != nullptr ? getResParamValueFloat_(*res_param, user_instance) : param_define_table->getAssetParamDefaultValueFloat(id);
            }
            return 0.0f;
        }

    }

    return 0.0f;
}

bool ResourceAccessor::isCustomParamString(u32 custom_param_idx) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    u32 id {param_define_table->getNumCustomParam() + custom_param_idx};

    if (id >= param_define_table->getNumAssetParam()) {
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();
        system->addError(Error::Type::CustomParamAccessFailed, user, "customParamIdx[%d] is not found", custom_param_idx);
        return false;
    }

    return param_define_table->getAssetParamType(id) == ParamValueType::String;
}

bool ResourceAccessor::isCustomParamString(const char* name) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    s32 id = param_define_table->searchAssetParamIdxFromCustomParamName(name);

    if (id < 0)
        return false;
    
    return param_define_table->getAssetParamType(id) == ParamValueType::String;
}

bool ResourceAccessor::isCustomParamBool(u32 custom_param_idx) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    u32 id {param_define_table->getNumCustomParam() + custom_param_idx};

    if (id < param_define_table->getNumAssetParam())
        return param_define_table->getAssetParamType(id) == ParamValueType::Bool;
    
    System* system = mpSystem;
    User* user {};
    if (mpUserResource != nullptr)
        user = mpUserResource->getUser();
    system->addError(Error::Type::CustomParamAccessFailed, user, "customParamIdx[%d] is not found", custom_param_idx);
    return false;
}

bool ResourceAccessor::isCustomParamBool(const char* name) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    s32 id = param_define_table->searchAssetParamIdxFromCustomParamName(name);

    if (id < 0)
        return false;
    
    return param_define_table->getAssetParamType(id) == ParamValueType::Bool;
}

bool ResourceAccessor::isCustomParamInt(u32 custom_param_idx) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    u32 id {param_define_table->getNumCustomParam() + custom_param_idx};

    if (id >= param_define_table->getNumAssetParam()) {
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();
        system->addError(Error::Type::CustomParamAccessFailed, user, "customParamIdx[%d] is not found", custom_param_idx);
        return false;
    }

    return param_define_table->getAssetParamType(id) == ParamValueType::UInt32;
}

bool ResourceAccessor::isCustomParamInt(const char* name) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    s32 id = param_define_table->searchAssetParamIdxFromCustomParamName(name);

    if (id < 0)
        return false;
    
    return param_define_table->getAssetParamType(id) == ParamValueType::UInt32;
}

bool ResourceAccessor::isCustomParamFloat(u32 custom_param_idx) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    u32 id {param_define_table->getNumCustomParam() + custom_param_idx};

    if (id >= param_define_table->getNumAssetParam()) {
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();
        system->addError(Error::Type::CustomParamAccessFailed, user, "customParamIdx[%d] is not found", custom_param_idx);
        return false;
    }

    return param_define_table->getAssetParamType(id) == ParamValueType::Float;
}

bool ResourceAccessor::isCustomParamFloat(const char* name) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    s32 id = param_define_table->searchAssetParamIdxFromCustomParamName(name);

    if (id < 0)
        return false;
    
    return param_define_table->getAssetParamType(id) == ParamValueType::Float;
}

bool ResourceAccessor::isCustomParamValueUsingCurve(u32 idx, const ResAssetCallTable& asset_ctb) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    u32 id {param_define_table->getNumCustomParam() + idx};

    if (id < param_define_table->getNumAssetParam())
        return isParamTypeEqual(ValueReferenceType::Curve, asset_ctb, id);
    
    System* system = mpSystem;
    User* user {};
    if (mpUserResource != nullptr)
        user = mpUserResource->getUser();
    system->addError(Error::Type::CustomParamAccessFailed, user, "customParamIdx[%d] is not found", idx);

    return false;
}

bool ResourceAccessor::isParamTypeEqual(ValueReferenceType ref_type, const ResAssetCallTable& asset_ctb, u32 idx) const
{
    return static_cast<ParamValueType>(ref_type) == getParamType(asset_ctb, idx);
}

const char* ResourceAccessor::getUserCustomParamValueString(s32 idx) const
{
    u32 id {mpSystem->getParamDefineTable()->getNumCustomUserParam() + idx};

    ResParam* user_params {mpUserResource->getParam()->userParamArray};
    u32 name_table_pos {mpUserResource->getParam()->commonResourceParam->nameTablePos};
    u32 param_raw_value {user_params[id].getValue()};

    u32 value_pos {name_table_pos + param_raw_value};
    const char* value_str {calcOffset<const char>(value_pos)};
    return value_str;
}

bool ResourceAccessor::isOutOfRangeUserCustom_(u32 /*unused*/) const { return false; }
bool ResourceAccessor::isMismatchTypeUserCustom_(u32 /*unused*/, ParamValueType /*unused*/, const char* /*unused*/) const { return false; }

bool ResourceAccessor::getUserCustomParamValueBool(s32 idx) const
{
    return getUserCustomParamValueInt(idx);
}

s32 ResourceAccessor::getUserCustomParamValueInt(s32 idx) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    u32 num_custom_user_param {param_define_table->getNumCustomUserParam()};

    u32 param_value {mpUserResource->getParam()->userParamArray[num_custom_user_param + idx].getValue()};
    s32 direct_value {mpUserResource->getParam()->commonResourceParam->directValueTable[param_value]};

    return direct_value;
}

f32 ResourceAccessor::getUserCustomParamValueFloat(s32 idx, const UserInstance* user_instance) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    u32 num_custom_user_param {param_define_table->getNumCustomUserParam()};

    return getResParamValueFloat_(mpUserResource->getParam()->userParamArray[num_custom_user_param + idx], user_instance);
}

const char* ResourceAccessor::getUserCustomParamValueString(const char* name) const
{
    s32 id {mpSystem->getParamDefineTable()->searchUserParamIdxFromCustomParamName(name)};

    ResParam* user_params {mpUserResource->getParam()->userParamArray};
    u32 name_table_pos {mpUserResource->getParam()->commonResourceParam->nameTablePos};
    u32 param_raw_value {user_params[id].getValue()};

    u32 value_pos {name_table_pos + param_raw_value};
    const char* value_str {calcOffset<const char>(value_pos)};
    return value_str;
}

bool ResourceAccessor::isOutOfRangeUserCustom_(const char* /*unused*/) const { return false; }
bool ResourceAccessor::isMismatchTypeUserCustom_(const char* /*unused*/, ParamValueType /*unused*/, const char* /*unused*/) const { return false; }

bool ResourceAccessor::getUserCustomParamValueBool(const char* name) const
{
    return getUserCustomParamValueInt(name);
}

s32 ResourceAccessor::getUserCustomParamValueInt(const char* name) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    s32 idx {param_define_table->searchUserParamIdxFromCustomParamName(name)};

    u32 param_value {mpUserResource->getParam()->userParamArray[idx].getValue()};
    s32 direct_value {mpUserResource->getParam()->commonResourceParam->directValueTable[param_value]};

    return direct_value;
}

f32 ResourceAccessor::getUserCustomParamValueFloat(const char* name, const UserInstance* user_instance) const
{
    auto* param_define_table {mpSystem->getParamDefineTable()};
    s32 idx {param_define_table->searchUserParamIdxFromCustomParamName(name)};

    return getResParamValueFloat_(mpUserResource->getParam()->userParamArray[idx], user_instance);
}

ParamValueType ResourceAccessor::getParamType(const ResAssetCallTable& asset_ctb, u32 idx) const
{
    if (checkAndErrorIsAsset_(asset_ctb, "")) {
        const ResParam* res_param {getResParamFromAssetParamPos(asset_ctb.paramStartPos, idx)};
        if (res_param != nullptr)
            return static_cast<ParamValueType>(res_param->getRefType());
        
        ParamValueType value_type {mpSystem->getParamDefineTable()->getAssetParamType(idx)};
        if (value_type != ParamValueType::String)
            return static_cast<ParamValueType>((value_type == ParamValueType::Unknown) * 4);
        
        return ParamValueType::Float;
    }

    return ParamValueType::UInt32;
}

// NON-MATCHING: swapped registers
const ResCurveCallTable* ResourceAccessor::getCurveCallTable(const ResAssetCallTable& asset_ctb, u32 idx) const
{
    if (checkAndErrorIsAsset_(asset_ctb, "") && getParamType(asset_ctb, idx) == ParamValueType::Bool) {
        if (mpUserResource != nullptr) {
            ResParam* param {calcOffset<ResParam>(asset_ctb.paramStartPos)};
            ResCurveCallTable* curve_ctb {mpUserResource->getParam()->commonResourceParam->curveCallTable};
            return curve_ctb != nullptr ? 
                   &curve_ctb[param[idx].getValue()] : 
                   nullptr;
        }
    }

    return nullptr;
}

f32 ResourceAccessor::getRandomValue(const ResRandomCallTable& random_ctb, f32 base) const
{
    f32 range {sead::MathCalcCommon<f32>::abs(random_ctb.maxValue - random_ctb.minValue) / 2};

    f32 random_f32 {mpSystem->getRandom()->getF32() * 2};
    f32 random_value {random_f32 - 1.0f};
    random_f32 = sead::MathCalcCommon<f32>::abs(random_f32 - 1.0f);

    f32 power_range {sead::MathCalcCommon<f32>::pow(random_f32, base) * range};
    f32 result = {random_ctb.minValue + range + (random_value >= 0.0f ? power_range : -power_range)};
    return result;
}

f32 ResourceAccessor::getRandomValue(const ResRandomCallTable& random_ctb) const
{
   return mpSystem->getRandom()->getF32Range(random_ctb.minValue, random_ctb.maxValue);
}

f32 ResourceAccessor::getRandomValueWeightMin(const ResRandomCallTable& random_ctb, f32 exp) const
{
    f32 range {sead::MathCalcCommon<f32>::abs(random_ctb.maxValue - random_ctb.minValue)};

    f32 random_f32 {mpSystem->getRandom()->getF32() + 0.0f};
    f32 random_value {sead::MathCalcCommon<f32>::pow(random_f32, exp) * range};
    return random_ctb.minValue + random_value;
}

// NON-MATCHING: swapped register
f32 ResourceAccessor::getRandomValueWeightMax(const ResRandomCallTable& random_ctb, f32 exp) const
{
    f32 range {sead::MathCalcCommon<f32>::abs(random_ctb.maxValue - random_ctb.minValue)};

    f32 random_f32 {mpSystem->getRandom()->getF32() + 0.0f};
    f32 random_value {(1 - sead::MathCalcCommon<f32>::pow(random_f32, exp)) * range};
    return random_ctb.minValue + random_value;
}

s32 ResourceAccessor::getContainerChildNum(const ResAssetCallTable& asset_ctb) const
{
    if (!asset_ctb.flag.isOnBit(0)) 
        return 0;
    
    auto* container_param {calcOffset<ResContainerParam>(asset_ctb.paramStartPos)};
    if (container_param != nullptr)
        return getContainerChildNum(*container_param);

    mpSystem->addError(Error::Type::ResourceAccessFailed, mpUserResource->getUser(), "getContainer error");
    return 0;
}

s32 ResourceAccessor::getContainerChildNum(const ResContainerParam& container_param) const
{
   
    if (container_param.childrenStartIndex >= 0 && container_param.childrenEndIndex >= 0 && 
        container_param.childrenEndIndex >= container_param.childrenStartIndex)
            return (1 - container_param.childrenStartIndex) + container_param.childrenEndIndex;

    setError_("invalid children num (start=%d, end=%d)", container_param.childrenStartIndex, container_param.childrenEndIndex);

    return 0;
}

const ResAssetCallTable* ResourceAccessor::getContainerChildCallTable(const ResContainerParam& container_param, u32 idx) const
{
    return getCallTable(container_param.childrenStartIndex + idx);
}

bool ResourceAccessor::isParamOverwritten(u32 param_pos, u32 trigger_idx) const
{
    s32 overwrite_id {getTriggerOverwriteParamId_(trigger_idx)};

    if (param_pos != 0 && overwrite_id >= 0) {
        sead::BitFlag32* mask {calcOffset<sead::BitFlag32>(param_pos)};
        return mask->isOnBit(overwrite_id);
    }

    return false;
}

// NON-MATCHING: missing two instructions
bool ResourceAccessor::isOverwriteParamTypeEqual(ValueReferenceType type, const ResTriggerOverwriteParam& overwrite_param, u32 idx) const
{
    s32 overwrite_id {getTriggerOverwriteParamId_(idx)};
    
    if (&overwrite_param != 0 && overwrite_id >= 0) {
        auto* mask = calcOffset<sead::BitFlag32>(reinterpret_cast<u64>(&overwrite_param));
        if (mask->isOnBit(overwrite_id)) {
            s32 param_idx {mask->countRightOnBit(overwrite_id)};
            return reinterpret_cast<ResParam*>(mask)[param_idx].getRefType() == type;
        }
    }
    
    return false;
}

const ResParam* ResourceAccessor::getResParamFromOverwriteParamPos_(u32 param_start_pos, u32 overwrite_idx) const
{
    s32 overwrite_id {getTriggerOverwriteParamId_(overwrite_idx)};
    
    if (param_start_pos != 0 && overwrite_id >= 0) {
        auto* mask = calcOffset<sead::BitFlag32>(param_start_pos);
        if (mask->isOnBit(overwrite_id)) {
            s32 param_idx {mask->countRightOnBit(overwrite_id) - 1};
            return &reinterpret_cast<ResParam*>(mask + 1)[param_idx];
        }
    }

    return nullptr;
}

const ResRandomCallTable* ResourceAccessor::getResRandomCallTable_(const ResParam& res_param) const 
{
    ResRandomCallTable* random_ctb {mpUserResource->getParam()->commonResourceParam->randomCallTable};
    if (random_ctb != nullptr)
        return &random_ctb[res_param.getValue()];

    return nullptr;
}

f32 ResourceAccessor::getResOverwriteParamValueFloat_(u32 param_idx, u32 overwrite_idx, const UserInstance* user_instance) const
{
    const ResParam* res_param {getResParamFromOverwriteParamPos_(param_idx, overwrite_idx)};
    if (res_param != nullptr)
        return getResParamValueFloat_(*res_param, user_instance);

    return 0.0f;
}

const char* ResourceAccessor::getResOverwriteParamValueString_(u32 param_idx, u32 overwrite_idx) const
{
    s32 overwrite_id {getTriggerOverwriteParamId_(overwrite_idx)};
    
    if (param_idx != 0 && overwrite_id >= 0) {
        auto* mask = calcOffset<sead::BitFlag32>(param_idx);
        if (mask->isOnBit(overwrite_id)) {
            s32 param_idx {mask->countRightOnBit(overwrite_id)};
            auto* res_param = &reinterpret_cast<ResParam*>(mask)[param_idx];
            return getResParamValueString_(*res_param);
        }
    }


    return "";
}


}  // namespace xlink2