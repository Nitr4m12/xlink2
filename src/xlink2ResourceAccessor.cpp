#include "xlink2/xlink2ResourceAccessor.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
ResourceAccessor::~ResourceAccessor() = default;

const ResAssetCallTable* ResourceAccessor::searchCallTable(const char* name) const {
    if (mUserResource && mSystem->isCallEnabled()) {
        UserResourceParam* param;
        if (ResMode::Editor >= mUserResource->getResMode())
            param = mUserResource->getParams()[(s32)mUserResource->getResMode()];
        else
            param = mUserResource->getParams()[0];

        if (param && param->isSetup)
            return mUserResource->searchAssetCallTableByName(name);
    }

    return nullptr;
}

const ResAssetCallTable* ResourceAccessor::searchCallTable(Locator* locator,
                                                           const char* name) const {
    if (mUserResource && mSystem->isCallEnabled()) {
        UserResourceParam* param;
        if (ResMode::Editor >= mUserResource->getResMode())
            param = mUserResource->getParams()[(s32)mUserResource->getResMode()];
        else
            param = mUserResource->getParams()[0];

        if (param && param->isSetup)
            return mUserResource->searchAssetCallTableByName(locator, name);
    }

    // why does this work?? it's probably wrong
    return (ResAssetCallTable*)mUserResource;
}

const ResAssetCallTable* ResourceAccessor::getCallTable(u32 idx) const {
    if (mUserResource && mSystem->isCallEnabled()) {
        UserResourceParam* param;
        if (ResMode::Editor >= mUserResource->getResMode())
            param = mUserResource->getParams()[(s32)mUserResource->getResMode()];
        else
            param = mUserResource->getParams()[0];

        if (param && param->isSetup) {
            if (idx < mUserHeader->numCallTable)
                return mUserResource->getAssetCallTableItem(idx);

            setError_("getCallTable: idx(%d) >= numCallTable(%d)", idx, mUserHeader->numCallTable);
        }
    }

    return nullptr;
}

void ResourceAccessor::setError_(const char*, ...) const {};

const char* ResourceAccessor::getKeyName(const ResAssetCallTable& call_table) const {
    return solveOffset<char>(call_table.params[0].keyNamePos);
}

// WIP
ContainerType ResourceAccessor::getCallTableType(const ResAssetCallTable& call_table) const {
    if (isContainer(call_table))
        return ContainerType::Asset;

    ResContainerParam* container_param{
        solveOffset<ResContainerParam>(call_table.params[0].paramStartPos)};
    if (container_param) {
        if (ContainerType::Sequence >= container_param->type) {
            char* container_name{solveOffset<char>(call_table.params[0].keyNamePos)};
            setError_("[%s] invalid container type(=%d)", container_name, container_param->type);
            return ContainerType::Asset;
        }
        return container_param->type;
    }

    return ContainerType::Asset;
}

const ContainerBase* ResourceAccessor::getContainer(const ResAssetCallTable& call_table) const {
    if (isContainer(call_table))
        return solveOffset<ContainerBase>(call_table.params[0].paramStartPos);
    return nullptr;
}

const sead::SafeString* ResourceAccessor::getCallTableTypeName(const ResAssetCallTable&) const {};

bool ResourceAccessor::isContainer(const ResAssetCallTable& call_table) const {
    return call_table.params[0].flag & 1;
};

// WIP
const char*
ResourceAccessor::getCustomParamValueString(u32 idx, const ResAssetCallTable& call_table) const {
    ParamDefineTable* param_define {mSystem->getParamDefineTable()};
    u32 id = param_define->getNumCustomParam() + idx;
    if (id < param_define->getNumAssetParam()) {
        ParamValueType value_type {param_define->getAssetParamType(id)};
        if (value_type == ParamValueType::String) {
            auto check {checkAndErrorIsAsset_(call_table, "getCustomParamValueString(%d)", idx)};
            if (check) {
                auto* flag = solveOffset<sead::BitFlag64>(call_table.params[0].paramStartPos);

            }
        }
    }
};

// WIP
const char* ResourceAccessor::getResParamValueString_(const ResParam& param) const {
    UserResourceParam* resource_param {mUserResource->getParams()[(s32)mUserResource->getResMode()]};
    u64 value_string_pos = (*param.rawValue & 0xffffff) + resource_param->commonResourceParam->nameTablePos;
    return solveOffset<char>(value_string_pos);

}

}  // namespace xlink2