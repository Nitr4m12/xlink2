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

// WIP
const char* ResourceAccessor::getCustomParamValueString(u32 idx,
                                                        const ResAssetCallTable& asset_ctb) const
{
    ParamDefineTable* param_define {mpSystem->getParamDefineTable()};
    u32 id = param_define->getNumCustomParam() + idx;
    if (id < param_define->getNumAssetParam()) {
        ParamValueType value_type {param_define->getAssetParamType(id)};
        if (value_type == ParamValueType::String) {
            auto is_asset {checkAndErrorIsAsset_(asset_ctb, "getCustomParamValueString(%d)", idx)};
            if (is_asset) {
                auto* mask = calcOffset<sead::BitFlag64>(asset_ctb.paramStartPos);
                if (mask->countOnBit()) {
                    
                }
            }
        }
    }
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

bool ResourceAccessor::getCustomParamValueBool(u32 custom_param_idx, const ResAssetCallTable& asset_ctb) const
{

}

s32 ResourceAccessor::getResParamValueInt_(const ResParam& param) const
{
    UserResourceParam* user_resource_param {mpUserResource->getParam()};
    return user_resource_param->commonResourceParam->directValueTable[param.getValue()];
}

f32 ResourceAccessor::getRandomValue(const ResRandomCallTable& random_ctb, f32 base) const
{
    f32 random_value {random_ctb.maxValue - random_ctb.minValue};
    random_value = random_value > 0.0f ? random_value : -random_value;

    f32 random_value2 {mpSystem->getRandom()->getF32()};
    f32 random_value3 {(random_value2 * 2) - 1.0f};
    random_value2 = random_value3 > 0.0f ? random_value3 : -random_value3;

    f32 random_value4 {std::powf(random_value2, base)};
    random_value = random_value * 0.5f;

    f32 random_value5 {random_value * random_value4};
    f32 random_value6 = {random_ctb.minValue + random_value + (random_value3 >= 0.0f ? random_value5 : -random_value5)};
    return random_value6;
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