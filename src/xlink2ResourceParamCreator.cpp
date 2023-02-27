#include <cstddef>

#include "xlink2/xlink2ResourceParamCreator.h"
#include "xlink2/xlink2Util.h"

namespace xlink2::ResourceParamCreator {
// NON-MATCHING
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

// NON-MATCHING
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

// NON-MATCHING
void createCommonResourceParam_(CommonResourceParam* common_res_param, BinAccessor* bin_accessor) {
    ResourceHeader* res_header{bin_accessor->mResourceHeader};
    EditorHeader* editor_header{bin_accessor->mEditorHeader};
    u32* ptr_follower;

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->numResParam;
    else
        ptr_follower = &bin_accessor->mResourceHeader->numResParam;
    common_res_param->numResParam = *ptr_follower;

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->numResAssetParam;
    else
        ptr_follower = &bin_accessor->mResourceHeader->numResAssetParam;

    common_res_param->numResAssetParam = *ptr_follower;

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->numResTriggerOverwriteParam;
    else
        ptr_follower = &bin_accessor->mResourceHeader->numResTriggerOverwriteParam;

    common_res_param->numResTriggerOverwriteParam = *ptr_follower;

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->numLocalPropertyNameRefTable;
    else
        ptr_follower = &bin_accessor->mResourceHeader->numLocalPropertyNameRefTable;

    common_res_param->numLocalPropertyNameRefTable = *ptr_follower;

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->numLocalPropertyEnumNameRefTable;
    else
        ptr_follower = &bin_accessor->mResourceHeader->numLocalPropertyEnumNameRefTable;

    common_res_param->numLocalPropertyEnumNameRefTable = *ptr_follower;

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->numDirectValueTable;
    else
        ptr_follower = &bin_accessor->mResourceHeader->numDirectValueTable;

    common_res_param->numDirectValueTable = *ptr_follower;

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->numRandomTable;
    else
        ptr_follower = &bin_accessor->mResourceHeader->numRandomTable;

    common_res_param->numRandomTable = *ptr_follower;

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->numCurveTable;
    else
        ptr_follower = &bin_accessor->mResourceHeader->numCurveTable;

    common_res_param->numCurveTable = *ptr_follower;

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->numCurvePointTable;
    else
        ptr_follower = &bin_accessor->mResourceHeader->numCurvePointTable;

    common_res_param->numCurvePointTable = *ptr_follower;

    if (common_res_param->numResAssetParam != 0) {
        ResAssetCallTable* res_asset_table{
            (ResAssetCallTable*)(bin_accessor->mBinEnd | sMinAddressHigh)};
        if (bin_accessor->mBinEnd < sMinAddressLow) {
            res_asset_table += 0x8000000;
        }
        common_res_param->resAssetCallTable = res_asset_table;
    }

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->triggerOverwriteParamTablePos;
    else
        ptr_follower = &bin_accessor->mResourceHeader->triggerOverwriteParamTablePos;

    if (common_res_param->numResTriggerOverwriteParam != 0)
        common_res_param->triggerOverwriteParamTablePos = *ptr_follower + bin_accessor->mBinStart;

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->localPropertyNameRefTablePos;
    else
        ptr_follower = &bin_accessor->mResourceHeader->localPropertyNameRefTablePos;

    u32* localPropertyRefTable{(u32*)(bin_accessor->mBinStart + *ptr_follower | sMinAddressHigh)};

    if (bin_accessor->mBinStart + *ptr_follower < sMinAddressLow)
        localPropertyRefTable += 0x100000000;

    if (common_res_param->numLocalPropertyNameRefTable != 0)
        common_res_param->localPropertyNameRefTable = localPropertyRefTable;
    ptr_follower = localPropertyRefTable + common_res_param->numLocalPropertyNameRefTable;

    if (common_res_param->numLocalPropertyEnumNameRefTable != 0)
        common_res_param->localPropertyEnumNameRefTable = ptr_follower;
    ptr_follower += common_res_param->numLocalPropertyEnumNameRefTable;

    if (common_res_param->numDirectValueTable != 0)
        common_res_param->directValueTable = ptr_follower;
    ptr_follower += common_res_param->numDirectValueTable;

    if (common_res_param->numRandomTable != 0)
        common_res_param->randomCallTable = ptr_follower;
    ptr_follower += common_res_param->numRandomTable;

    if (common_res_param->numCurveTable != 0)
        common_res_param->curveCallTable = ptr_follower;
    ptr_follower += common_res_param->numCurveTable;

    if (common_res_param->numCurvePointTable != 0)
        common_res_param->curvePointTable = ptr_follower;

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->exDataRegionPos;
    else
        ptr_follower = &bin_accessor->mResourceHeader->exRegionPos;

    common_res_param->exRegionPos = bin_accessor->mBinStart + *ptr_follower;

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->conditionTablePos;
    else
        ptr_follower = &bin_accessor->mResourceHeader->conditionTablePos;

    common_res_param->conditionTablePos = bin_accessor->mBinStart + *ptr_follower;

    if (!bin_accessor->mResourceHeader)
        ptr_follower = &bin_accessor->mEditorHeader->nameTablePos;
    else
        ptr_follower = &bin_accessor->mResourceHeader->nameTablePos;

    common_res_param->nameTablePos = bin_accessor->mBinStart + *ptr_follower;
}

// NON-MATCHING
void dumpRomResource_(ResourceHeader* res_header, RomResourceParam* rom_res,
                      const BinAccessor* bin_accessor, const ParamDefineTable* param_define,
                      sead::Heap* heap, bool p1, sead::BufferedSafeString* buffered_str) {
    // TODO
    // sead::BufferedSafeString dump_str;

    dumpLine_(buffered_str, "[XLink2] ResourceBuffer dump \n");
    dumpLine_(buffered_str, "<< ResourceHeader (addr:0x%x, size:%@) >>\n", res_header, 0x48);

    dumpLine_(buffered_str, "  magic: %s\n" /*, dump_str.mStringTop*/);
    dumpLine_(buffered_str, "  dataSize: %@\n", res_header->dataSize);
    dumpLine_(buffered_str, "  version: %@\n", res_header->version);
    dumpLine_(buffered_str, "  numResParam: %@\n", res_header->numResParam);
    dumpLine_(buffered_str, "  numResAssetParam: %@\n", res_header->numResAssetParam);
    dumpLine_(buffered_str, "  numResTriggerOverwriteParam: %@\n",
              res_header->numResTriggerOverwriteParam);
    dumpLine_(buffered_str, "  triggerOverwriteParamTablePos: %@\n",
              res_header->triggerOverwriteParamTablePos);
    dumpLine_(buffered_str, "  localPropertyNameRefTablePos: %@\n",
              res_header->localPropertyNameRefTablePos);
    dumpLine_(buffered_str, "  numLocalPropertyNameRefTable: %@\n",
              res_header->numLocalPropertyNameRefTable);
    dumpLine_(buffered_str, "  numLocalPropertyEnumNameRefTable: %@\n",
              res_header->numLocalPropertyEnumNameRefTable);
    dumpLine_(buffered_str, "  numDirectValueTable: %@\n", res_header->numDirectValueTable);
    dumpLine_(buffered_str, "  numRandomTable: %@\n", res_header->numRandomTable);
    dumpLine_(buffered_str, "  numCurveTable: %@\n", res_header->numCurveTable);
    dumpLine_(buffered_str, "  numCurvePointTable: %@\n", res_header->numCurvePointTable);
    dumpLine_(buffered_str, "  numUser: %@\n", res_header->numUser);
    dumpLine_(buffered_str, "  conditionTablePos: %@\n", res_header->conditionTablePos);
    dumpLine_(buffered_str, "  nameTablePos: %@\n", res_header->nameTablePos);
    dumpLine_(buffered_str, "\n");

    u32 num_user{res_header->numUser << 2};

    dumpLine_(buffered_str, "<< OffsetTable (addr:0x%x, size:%@*%@=%@) >>\n", rom_res->binPos, 4,
              res_header->numUser, num_user);
    if (res_header->numUser != 0) {
        for (int i{0}; i < res_header->numUser; ++i) {
            dumpLine_(buffered_str, "  [%d] binPos=%@, nameHash=%@\n", i,
                      rom_res->binPos + static_cast<long>(i * 4),
                      rom_res->nameHash + static_cast<long>(i * 4));
        }
    }
    dumpLine_(buffered_str, "\n");

    dumpLine_(buffered_str, "<< ParamDefineTable (addr:0x%x, size:%@) >>\n",
              rom_res->binPos + num_user, param_define->getNumUserParams());
    dumpLine_(buffered_str, "  ...no content print.\n\n");

    dumpCommonResourceFront_(rom_res, bin_accessor, p1, buffered_str);
    if (p1 && res_header->numUser != 0) {
        for (int i{0}; i < res_header->numUser; ++i) {
            u32 v1 =
                (ulong)(bin_accessor->mBinStart + *(int*)(*(long*)&rom_res->binPos + (ulong)i * 4));
            auto* v2 = (ResUserHeader*)(v1 | sMinAddressHigh);
            sead::SafeString str_v{""};
            if (v1 < sMinAddressLow) {
                v2 = (ResUserHeader*)&v2[0x5555555].numRandomContainer;
            }
            dumpUserBin_(i, str_v, v2, param_define, buffered_str);
        }
    }
    dumpCommonResourceRear_(rom_res, bin_accessor, res_header->dataSize, heap, false, buffered_str);
}

// NON-MATCHING
void dumpEditorResource_(EditorResourceParam* editor_resource, const BinAccessor* bin_accessor,
                         const ParamDefineTable* param_define, sead::Heap* heap) {

    sead::BufferedSafeString* buffered_str{nullptr};

    dumpLine_(buffered_str, "[XLink2] EditorBuffer dump\n");

    EditorHeader* editor_header {editor_resource->pEditorHeader};
    sead::SafeString* editor_name {editor_resource->editorName};

    dumpLine_(buffered_str, "<< EditorHeader[%s] (addr:0x%x, size:%@) >>\n", editor_resource->editorName2, editor_header, 0x44);
    dumpLine_(buffered_str, "  numResParam: %@\n", editor_header->numResParam);
    dumpLine_(buffered_str, "  numResAssetParam: %@\n", editor_header->numResAssetParam);
    dumpLine_(buffered_str, "  numResTriggerOverwriteParam: %@\n", editor_header->numResTriggerOverwriteParam);
    dumpLine_(buffered_str, "  numLocalPropertyNameRefTable: %@\n", editor_header->numLocalPropertyNameRefTable);
    dumpLine_(buffered_str, "  numLocalPropertyEnumNameRefTable: %@\n", editor_header->numLocalPropertyEnumNameRefTable);
    dumpLine_(buffered_str, "  numDirectValueTable: %@\n", editor_header->numDirectValueTable);
    dumpLine_(buffered_str, "  numRandomTable: %@\n", editor_header->numRandomTable);
    dumpLine_(buffered_str, "  numCurveTable: %@\n", editor_header->numCurveTable);
    dumpLine_(buffered_str, "  numCurvePointTable: %@\n", editor_header->numCurvePointTable);
    dumpLine_(buffered_str, "  exDataRegionPos: %@\n", editor_header->exDataRegionPos);
    dumpLine_(buffered_str, "  userNamePos: %@\n", editor_header->userNamePos);
    dumpLine_(buffered_str, "  userBinPos: %@\n", editor_header->userBinPos);
    dumpLine_(buffered_str, "  conditionTablePos: %@\n", editor_header->conditionTablePos);
    dumpLine_(buffered_str, "  nameTablePos: %@\n", editor_header->nameTablePos);
    dumpLine_(buffered_str, "\n");

    dumpCommonResourceFront_(editor_resource, bin_accessor, true, buffered_str);
    dumpUserBin_(0, *editor_name, editor_resource->pResUserHeader, param_define, buffered_str);
    dumpCommonResourceRear_(editor_resource, bin_accessor, editor_resource->_0, heap, false, buffered_str);
}

void dumpCommonResourceFront_(CommonResourceParam *, const BinAccessor *, bool, sead::BufferedSafeString *);
void dumpUserBin_(u32, const sead::SafeString &, ResUserHeader *, const ParamDefineTable *, sead::BufferedSafeString *);
void dumpCommonResourceRear_(CommonResourceParam *, const BinAccessor *, u32, sead::Heap *, bool, sead::BufferedSafeString *);
}  // namespace xlink2::ResourceParamCreator