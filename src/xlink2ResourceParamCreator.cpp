#include "xlink2/xlink2ResourceParamCreator.h"
#include "xlink2/xlink2Util.h"

namespace xlink2::ResourceParamCreator {
BinAccessor::BinAccessor(ResourceHeader* res_header, ParamDefineTable const* param_define) {
    mResourceHeader = res_header;
    mEditorHeader = nullptr;
    mBinStart = (long)res_header;
    mBinEnd = (long)res_header + res_header->numUser * 8 + param_define->getNumUserParams() + 0x48;
    mUserParamNum = param_define->getUserParamNum();
    mAssetParamNum = param_define->getAssetParamNum();
}

BinAccessor::BinAccessor(EditorHeader* editor_header, ParamDefineTable const* param_define) {
    mResourceHeader = nullptr;
    mEditorHeader = editor_header;
    mBinStart = (long)editor_header;
    mBinEnd = (long)editor_header + 0x44;
    mUserParamNum = param_define->getUserParamNum();
    mAssetParamNum = param_define->getAssetParamNum();
}

// TODO
void createParamAndSolveResource(RomResourceParam* rom_res_param, void* p2,
                                 ParamDefineTable const* param_define, System* system) {
    rom_res_param->resAssetCallTable = nullptr;
    rom_res_param->triggerOverwriteParamTablePos = 0;
    rom_res_param->numCurvePointTable = 0;
    rom_res_param->numLocalPropertyEnumNameRefTable = 0;
    rom_res_param->numRandomTable = 0;

    s64 res_end{(long)p2 + 0x48};

    rom_res_param->nameTablePos = 0;
    rom_res_param->localPropertyNameRefTable = nullptr;
    rom_res_param->_1 = 0;
    rom_res_param->_0 = p2;
    rom_res_param->numResParam = 0;
    rom_res_param->numResTriggerOverwriteParam = 0;
    rom_res_param->curvePointTable = nullptr;
    rom_res_param->conditionTablePos = 0;
    rom_res_param->randomCallTable = nullptr;
    rom_res_param->curveCallTable = nullptr;
    rom_res_param->localPropertyEnumNameRefTable = nullptr;
    rom_res_param->directValueTable = nullptr;
    rom_res_param->nameHash = 0;
    rom_res_param->binPos = 0;
}

// TODO
void createCommonResourceParam_(CommonResourceParam* common_res_param, BinAccessor* bin_accessor) {
    u32* numResParam;
    ResourceHeader* res_header {bin_accessor->mResourceHeader};
    EditorHeader* editor_header {bin_accessor->mEditorHeader};

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->numResParam;
    else
        numResParam = &bin_accessor->mResourceHeader->numResParam;
    common_res_param->numResParam = *numResParam;

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->numResAssetParam;
    else
        numResParam = &bin_accessor->mResourceHeader->numResAssetParam;

    common_res_param->numResAssetParam = *numResParam;

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->numResTriggerOverwriteParam;
    else
        numResParam = &bin_accessor->mResourceHeader->numResTriggerOverwriteParam;

    common_res_param->numResTriggerOverwriteParam = *numResParam;

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->numLocalPropertyNameRefTable;
    else
        numResParam = &bin_accessor->mResourceHeader->numLocalPropertyNameRefTable;

    common_res_param->numLocalPropertyNameRefTable = *numResParam;

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->numLocalPropertyEnumNameRefTable;
    else
        numResParam = &bin_accessor->mResourceHeader->numLocalPropertyEnumNameRefTable;

    common_res_param->numLocalPropertyEnumNameRefTable = *numResParam;

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->numDirectValueTable;
    else
        numResParam = &bin_accessor->mResourceHeader->numDirectValueTable;

    common_res_param->numDirectValueTable = *numResParam;

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->numRandomTable;
    else
        numResParam = &bin_accessor->mResourceHeader->numRandomTable;

    common_res_param->numRandomTable = *numResParam;

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->numCurveTable;
    else
        numResParam = &bin_accessor->mResourceHeader->numCurveTable;

    common_res_param->numCurveTable = *numResParam;

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->numCurvePointTable;
    else
        numResParam = &bin_accessor->mResourceHeader->numCurvePointTable;

    common_res_param->numCurvePointTable = *numResParam;

    if (common_res_param->numResAssetParam != 0) {
        ResAssetCallTable* res_asset_table {(ResAssetCallTable*) (bin_accessor->mBinEnd | sMinAddressHigh)};
        if (bin_accessor->mBinEnd < sMinAddressLow) {
            res_asset_table += 0x8000000;
        }
        common_res_param->resAssetCallTable = res_asset_table;
    }

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->triggerOverwriteParamTablePos;
    else
        numResParam = &bin_accessor->mResourceHeader->triggerOverwriteParamTablePos;

    if (common_res_param->numResTriggerOverwriteParam != 0)
        common_res_param->triggerOverwriteParamTablePos = *numResParam + bin_accessor->mBinStart;

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->localPropertyNameRefTablePos;
    else
        numResParam = &bin_accessor->mResourceHeader->localPropertyNameRefTablePos;

    u32* localPropertyRefTable {(u32*)(bin_accessor->mBinStart + *numResParam | sMinAddressHigh)};

    if (bin_accessor->mBinStart + *numResParam < sMinAddressLow)
        localPropertyRefTable += 0x100000000;

    if (common_res_param->numLocalPropertyNameRefTable != 0)
        common_res_param->localPropertyNameRefTable = localPropertyRefTable;
    numResParam = localPropertyRefTable + common_res_param->numLocalPropertyNameRefTable;

    if (common_res_param->numLocalPropertyEnumNameRefTable != 0)
        common_res_param->localPropertyEnumNameRefTable = numResParam;
    numResParam += common_res_param->numLocalPropertyEnumNameRefTable;

    if (common_res_param->numDirectValueTable != 0)
        common_res_param->directValueTable = numResParam;
    numResParam += common_res_param->numDirectValueTable;

    if (common_res_param->numRandomTable != 0)
        common_res_param->randomCallTable = numResParam;
    numResParam += common_res_param->numRandomTable;

    if (common_res_param->numCurveTable != 0)
        common_res_param->curveCallTable = numResParam;
    numResParam += common_res_param->numCurveTable;

    if (common_res_param->numCurvePointTable != 0)
        common_res_param->curvePointTable = numResParam;

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->exRegionPos;
    else
        numResParam = &bin_accessor->mResourceHeader->exRegionPos;

    common_res_param->exRegionPos = bin_accessor->mBinStart + *numResParam;

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->conditionTablePos;
    else
        numResParam = &bin_accessor->mResourceHeader->conditionTablePos;

    common_res_param->conditionTablePos = bin_accessor->mBinStart + *numResParam;

    if (!bin_accessor->mResourceHeader)
        numResParam = &bin_accessor->mEditorHeader->nameTablePos;
    else
        numResParam = &bin_accessor->mResourceHeader->nameTablePos;

    common_res_param->nameTablePos = bin_accessor->mBinStart + *numResParam;

}
}  // namespace xlink2::ResourceParamCreator