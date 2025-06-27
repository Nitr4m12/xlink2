#include <cstdarg>

#include "xlink2/xlink2ResourceAccessor.h"
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
    ParamDefineTable* param_define_table {mpSystem->getParamDefineTable()};
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
        user_param->commonResourceParam->nameTablePos + (param.rawValue & 0xffffff);
    return calcOffset<char>(value_string_pos);
}

bool ResourceAccessor::getCustomParamValueBool(u32 idx, const ResAssetCallTable& asset_ctb) const
{
    ParamDefineTable* param_define_table {mpSystem->getParamDefineTable()};
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
    ParamDefineTable* param_define_table {mpSystem->getParamDefineTable()};
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
    ParamDefineTable* param_define_table {mpSystem->getParamDefineTable()};
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

    
    return 0.0f;
}

const char* ResourceAccessor::getCustomParamValueString(const char* name, const ResAssetCallTable& asset_ctb) const
{
    ParamDefineTable* param_define_table {mpSystem->getParamDefineTable()};
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
    ParamDefineTable* param_define_table {mpSystem->getParamDefineTable()};
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
    ParamDefineTable* param_define_table {mpSystem->getParamDefineTable()};
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
    ParamDefineTable* param_define_table {mpSystem->getParamDefineTable()};
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
    ParamDefineTable* param_define_table {mpSystem->getParamDefineTable()};
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
    ParamDefineTable* param_define_table {mpSystem->getParamDefineTable()};
    s32 id = static_cast<s32>(param_define_table->searchAssetParamIdxFromCustomParamName(name));

    if (id < 0)
        return false;
    
    return param_define_table->getAssetParamType(id) == ParamValueType::String;
}

bool ResourceAccessor::isCustomParamBool(u32 custom_param_idx) const
{
    ParamDefineTable* param_define_table {mpSystem->getParamDefineTable()};
    u32 id {param_define_table->getNumCustomParam() + custom_param_idx};

    if (id >= param_define_table->getNumAssetParam()) {
        System* system = mpSystem;
        User* user {};
        if (mpUserResource != nullptr)
            user = mpUserResource->getUser();
        system->addError(Error::Type::CustomParamAccessFailed, user, "customParamIdx[%d] is not found", custom_param_idx);
        return false;
    }

    return param_define_table->getAssetParamType(id) == ParamValueType::Bool;
}

bool ResourceAccessor::isCustomParamBool(const char* name) const
{
    ParamDefineTable* param_define_table {mpSystem->getParamDefineTable()};
    s32 id = static_cast<s32>(param_define_table->searchAssetParamIdxFromCustomParamName(name));

    if (id < 0)
        return false;
    
    return param_define_table->getAssetParamType(id) == ParamValueType::Bool;
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

f32 ResourceAccessor::getRandomValueWeightMin(const ResRandomCallTable& random_ctb, f32 base) const
{
    f32 random_value {random_ctb.maxValue - random_ctb.minValue};
    random_value = random_value > 0.0f ? random_value : -random_value;

    f32 random_value2 {mpSystem->getRandom()->getF32()};
    f32 random_value3 {std::powf(random_value2 + 0.0f, base)};
    f32 random_value4 {random_value3 * random_value};
    return random_ctb.minValue + random_value4;
}

}  // namespace xlink2