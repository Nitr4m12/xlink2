#include <cstdarg>

#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
ResourceAccessor::~ResourceAccessor() = default;

const ResAssetCallTable* ResourceAccessor::searchCallTable(const char* name) const
{
    if (mUserResource && mSystem->isCallEnabled()) {
        UserResourceParam* param = mUserResource->getParam();

        if (param && param->isSetup)
            return mUserResource->searchAssetCallTableByName(name);
    }

    return nullptr;
}

void ResourceAccessor::searchCallTable(Locator* locator, const char* name) const
{
    if (mUserResource && mSystem->isCallEnabled()) {
        UserResourceParam* param = mUserResource->getParam();

        if (param && param->isSetup)
            mUserResource->searchAssetCallTableByName(locator, name);
    }
}

const ResAssetCallTable* ResourceAccessor::getCallTable(u32 idx) const
{
    if (mUserResource && mSystem->isCallEnabled()) {
        UserResourceParam* param = mUserResource->getParam();

        if (param && param->isSetup) {
            if (idx < mUserHeader->numCallTable)
                return mUserResource->getAssetCallTableItem(idx);

            setError_("getCallTable: idx(%d) >= numCallTable(%d)", idx, mUserHeader->numCallTable);
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
    System* sys {mSystem};
    if (mUserResource != nullptr)
        user = mUserResource->getUser();

    sys->addError(Error::Type::ResourceAccessFailed, user, "%s", msg.getBuffer());
}

const char* ResourceAccessor::getKeyName(const ResAssetCallTable& call_table) const
{
    return calcOffset<char>(call_table.keyNamePos);
}

// WIP
ContainerType ResourceAccessor::getCallTableType(const ResAssetCallTable& call_table) const
{
    if (!isContainer(call_table))
        return ContainerType::Asset;

    ResContainerParam* container_param {calcOffset<ResContainerParam>(call_table.paramStartPos)};
    if (container_param) {
        if (container_param->type > ContainerType::Sequence) {
            char* container_name {calcOffset<char>(call_table.keyNamePos)};
            setError_("[%s] invalid container type(=%d)", container_name, container_param->type);
            return ContainerType::Asset;
        }
        return container_param->type;
    }

    return ContainerType::Asset;
}

const ContainerBase* ResourceAccessor::getContainer(const ResAssetCallTable& call_table) const
{
    if (isContainer(call_table))
        return calcOffset<ContainerBase>(call_table.paramStartPos);
    return nullptr;
}

// WIP
const sead::SafeString* ResourceAccessor::getCallTableTypeName(const ResAssetCallTable&) const 
{
    return nullptr;
}

bool ResourceAccessor::isContainer(const ResAssetCallTable& call_table) const
{
    return call_table.flag & 1;
}

// WIP
const char* ResourceAccessor::getCustomParamValueString(u32 idx,
                                                        const ResAssetCallTable& call_table) const
{
    ParamDefineTable* param_define {mSystem->getParamDefineTable()};
    u32 id = param_define->getNumCustomParam() + idx;
    if (id < param_define->getNumAssetParam()) {
        ParamValueType value_type {param_define->getAssetParamType(id)};
        if (value_type == ParamValueType::String) {
            auto is_asset {checkAndErrorIsAsset_(call_table, "getCustomParamValueString(%d)", idx)};
            if (is_asset) {
                auto* flag = calcOffset<sead::BitFlag64>(call_table.paramStartPos);
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
        System* sys {mSystem};
        if (mUserResource != nullptr)
            user = mUserResource->getUser();

        sys->addError(Error::Type::ResourceAccessFailed, user, "%s: [%s] is container", msg.getBuffer(), getKeyName(asset_ctb));
        return false;
    }
    return true;
}

const char* ResourceAccessor::getResParamValueString_(const ResParam& param) const
{
    UserResourceParam* user_param = mUserResource->getParam();
    u64 value_string_pos =
        user_param->commonResourceParam->nameTablePos + (param.rawValue & 0xffffff);
    return calcOffset<char>(value_string_pos);
}

bool ResourceAccessor::getCustomParamValueBool(u32 custom_param_idx, const ResAssetCallTable& asset_call_table) const
{

}

//WIP
s32 ResourceAccessor::getResParamValueInt_(const ResParam& param) const
{
    return mUserResource->getParam()->commonResourceParam->directValueTable[param.rawValue & 0xffffff];
}

}  // namespace xlink2