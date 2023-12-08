#include <cstddef>

#include "xlink2/xlink2Condition.h"
#include "xlink2/xlink2ResourceParamCreator.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
// NON-MATCHING
ResourceParamCreator::BinAccessor::BinAccessor(ResourceHeader* res_header,
                                               ParamDefineTable const* param_define)
{
    mResourceHeader = res_header;
    mEditorHeader = nullptr;
    mBinStart = (long)res_header;
    auto num_user = mResourceHeader->numUser * 8;
    auto num_user_params = param_define->getSize();
    mAssetsStart = mBinStart + num_user + num_user_params + sizeof(ResourceHeader);
    mNumUserParam = param_define->get0();
    mNumAssetParam = param_define->getNumAssetParam();
}

ResourceParamCreator::BinAccessor::BinAccessor(EditorHeader* editor_header,
                                               ParamDefineTable const* param_define)
{
    mResourceHeader = nullptr;
    mEditorHeader = editor_header;
    mBinStart = (long)editor_header;
    mAssetsStart = (long)editor_header + sizeof(EditorHeader);
    mNumUserParam = param_define->get0();
    mNumAssetParam = param_define->getNumAssetParam();
}

// NON-MATCHING
void ResourceParamCreator::createParamAndSolveResource(RomResourceParam* rom_res_param, void* p2,
                                                       ParamDefineTable const* param_define,
                                                       System* system)
{
    rom_res_param->assetParamTable = nullptr;
    rom_res_param->triggerOverwriteParamTablePos = 0;
    rom_res_param->numCurvePointTable = 0;
    rom_res_param->numLocalPropertyEnumNameRefTable = 0;
    rom_res_param->numRandomTable = 0;

    // s64 res_end{(long)p2 + 0x48};

    rom_res_param->nameTablePos = 0;
    rom_res_param->localPropertyNameRefTable = nullptr;
    rom_res_param->numUser = 0;
    rom_res_param->_0 = p2;
    rom_res_param->numResParam = 0;
    rom_res_param->numResTriggerOverwriteParam = 0;
    rom_res_param->curvePointTable = nullptr;
    rom_res_param->conditionTablePos = 0;
    rom_res_param->randomCallTable = nullptr;
    rom_res_param->curveCallTable = nullptr;
    rom_res_param->localPropertyEnumNameRefTable = nullptr;
    rom_res_param->directValueTable = nullptr;
    rom_res_param->nameHashTable = nullptr;
    rom_res_param->offsetTable = nullptr;
}

// WIP
void ResourceParamCreator::createCommonResourceParam_(CommonResourceParam* common_res_param,
                                                      BinAccessor* bin_accessor)
{
    // ResourceHeader* res_header{bin_accessor->mResourceHeader};
    // EditorHeader* editor_header{bin_accessor->mEditorHeader};
    u32* ptr;

    common_res_param->numResParam = bin_accessor->mResourceHeader ?
                                        bin_accessor->mResourceHeader->numResParam :
                                        bin_accessor->mEditorHeader->numResParam;
    common_res_param->numResAssetParam = bin_accessor->mResourceHeader ?
                                             bin_accessor->mResourceHeader->numResAssetParam :
                                             bin_accessor->mEditorHeader->numResAssetParam;
    common_res_param->numResTriggerOverwriteParam =
        bin_accessor->mResourceHeader ? bin_accessor->mResourceHeader->numResTriggerOverwriteParam :
                                        bin_accessor->mEditorHeader->numResTriggerOverwriteParam;
    common_res_param->numLocalPropertyNameRefTable =
        bin_accessor->mResourceHeader ?
            bin_accessor->mResourceHeader->numLocalPropertyNameRefTable :
            bin_accessor->mEditorHeader->numLocalPropertyNameRefTable;
    common_res_param->numLocalPropertyEnumNameRefTable =
        bin_accessor->mResourceHeader ?
            bin_accessor->mResourceHeader->numLocalPropertyEnumNameRefTable :
            bin_accessor->mEditorHeader->numLocalPropertyEnumNameRefTable;
    common_res_param->numDirectValueTable = bin_accessor->mResourceHeader ?
                                                bin_accessor->mResourceHeader->numDirectValueTable :
                                                bin_accessor->mEditorHeader->numDirectValueTable;
    common_res_param->numRandomTable = bin_accessor->mResourceHeader ?
                                           bin_accessor->mResourceHeader->numRandomTable :
                                           bin_accessor->mEditorHeader->numRandomTable;
    common_res_param->numCurveTable = bin_accessor->mResourceHeader ?
                                          bin_accessor->mResourceHeader->numCurveTable :
                                          bin_accessor->mEditorHeader->numCurveTable;
    common_res_param->numCurvePointTable = bin_accessor->mResourceHeader ?
                                               bin_accessor->mResourceHeader->numCurvePointTable :
                                               bin_accessor->mEditorHeader->numCurvePointTable;

    if (common_res_param->numResAssetParam > 0)
        common_res_param->assetParamTable =
            solveOffset<ResAssetParamTable>(bin_accessor->mAssetsStart);

    common_res_param->triggerOverwriteParamTablePos =
        bin_accessor->mResourceHeader ?
            bin_accessor->mResourceHeader->triggerOverwriteParamTablePos :
            bin_accessor->mEditorHeader->triggerOverwriteParamTablePos;
    if (common_res_param->numResTriggerOverwriteParam > 0)
        common_res_param->triggerOverwriteParamTablePos += bin_accessor->mBinStart;

    if (bin_accessor->mResourceHeader)
        ptr = &bin_accessor->mResourceHeader->localPropertyNameRefTablePos;
    else
        ptr = &bin_accessor->mEditorHeader->localPropertyNameRefTablePos;
    auto* local_property_name_ref_table = solveOffset<u32>(bin_accessor->mBinStart + *ptr);
    if (common_res_param->numLocalPropertyNameRefTable > 0)
        common_res_param->localPropertyNameRefTable = local_property_name_ref_table;

    ptr = common_res_param->localPropertyNameRefTable +
          common_res_param->numLocalPropertyNameRefTable;
    if (common_res_param->numLocalPropertyEnumNameRefTable > 0)
        common_res_param->localPropertyEnumNameRefTable = ptr;
    ptr = ptr + common_res_param->numLocalPropertyEnumNameRefTable;

    if (common_res_param->numDirectValueTable > 0)
        common_res_param->directValueTable = ptr;
    ptr = ptr + common_res_param->numDirectValueTable;

    auto* rrct_ptr = (ResRandomCallTable*)ptr;
    if (common_res_param->numRandomTable > 0)
        common_res_param->randomCallTable = rrct_ptr;

    auto* rcct_ptr = (ResCurveCallTable*)(rrct_ptr + common_res_param->numRandomTable);
    if (common_res_param->numCurveTable > 0)
        common_res_param->curveCallTable = rcct_ptr;

    auto* cpt_ptr = (CurvePoint*)(rcct_ptr + common_res_param->numCurveTable);
    if (common_res_param->numCurvePointTable > 0)
        common_res_param->curvePointTable = cpt_ptr;

    if (bin_accessor->mResourceHeader)
        ptr = &bin_accessor->mResourceHeader->exRegionPos;
    else
        ptr = &bin_accessor->mEditorHeader->exDataRegionPos;
    common_res_param->exRegionPos = *ptr + bin_accessor->mBinStart;

    if (bin_accessor->mResourceHeader)
        ptr = &bin_accessor->mResourceHeader->conditionTablePos;
    else
        ptr = &bin_accessor->mEditorHeader->conditionTablePos;
    common_res_param->conditionTablePos = *ptr + bin_accessor->mBinStart;

    if (bin_accessor->mResourceHeader)
        ptr = &bin_accessor->mResourceHeader->nameTablePos;
    else
        ptr = &bin_accessor->mEditorHeader->nameTablePos;
    common_res_param->nameTablePos = *ptr + bin_accessor->mBinStart;
}

// WIP
void ResourceParamCreator::dumpRomResource_(ResourceHeader* res_header, RomResourceParam* rom_res,
                                            const BinAccessor* bin_accessor,
                                            const ParamDefineTable* param_define, sead::Heap* heap,
                                            bool p1, sead::BufferedSafeString* buffered_str)
{
    dumpLine_(buffered_str, "[XLink2] ResourceBuffer dump\n");
    dumpLine_(buffered_str, "<< ResourceHeader (addr:0x%x, size:%@) >>\n", res_header,
              sizeof(ResourceHeader));

    sead::FixedSafeString<5> magic;
    magic.format((char*)res_header->magic);
    dumpLine_(buffered_str, "  magic: %s\n", magic.getBuffer());
    dumpLine_(buffered_str, "  dataSize: %@\n", res_header->dataSize);
    dumpLine_(buffered_str, "  version: %@\n", res_header->version);
    dumpLine_(buffered_str, "  numResParam: %@\n", res_header->numResParam);
    dumpLine_(buffered_str, "  numResAssetParam: %@\n", res_header->numResAssetParam);
    dumpLine_(buffered_str, "  numResTriggerOverwirteParam: %@\n",
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

    u32 offset_table_size = res_header->numUser * sizeof(u32);
    dumpLine_(buffered_str, "<< OffsetTable (addr:0x%x, size:%@*%@=%@) >>\n", rom_res->offsetTable,
              sizeof(u32), res_header->numUser, offset_table_size);
    if (res_header->numUser != 0) {
        for (u32 i{0}; i < res_header->numUser; ++i)
            dumpLine_(buffered_str, "  [%d] binPos=%@, nameHash=%@\n", i, rom_res->offsetTable[i],
                      rom_res->nameHashTable[i]);
    }
    dumpLine_(buffered_str, "\n");

    dumpLine_(buffered_str, "<< ParamDefineTable (addr:0x%x, size:%@) >>\n", rom_res->offsetTable,
              param_define->getSize());
    dumpLine_(buffered_str, "  ...no content print.\n\n");

    dumpCommonResourceFront_(rom_res, bin_accessor, p1, buffered_str);
    if (p1 && res_header->numUser != 0) {
        for (u32 i{0}; i < res_header->numUser; ++i) {
            u64 user_offset = bin_accessor->mBinStart + rom_res->offsetTable[i];
            dumpUserBin_(i, "", solveOffset<ResUserHeader>(user_offset), param_define,
                         buffered_str);
        }
    }
    dumpCommonResourceRear_(rom_res, bin_accessor, res_header->dataSize, heap, false, buffered_str);
}

// NON-MATCHING
void ResourceParamCreator::dumpEditorResource_(EditorResourceParam* editor_resource,
                                               const BinAccessor* bin_accessor,
                                               const ParamDefineTable* param_define,
                                               sead::Heap* heap)
{
    sead::BufferedSafeString* buffered_str{nullptr};

    dumpLine_(buffered_str, "[XLink2] EditorBuffer dump\n");

    EditorHeader* editor_header{editor_resource->pEditorHeader};
    sead::FixedSafeString<64> editor_name{editor_resource->editorName};

    dumpLine_(buffered_str, "<< EditorHeader[%s] (addr:0x%x, size:%@) >>\n",
              editor_resource->editorName.getBuffer(), editor_header, 0x44);
    dumpLine_(buffered_str, "  numResParam: %@\n", editor_header->numResParam);
    dumpLine_(buffered_str, "  numResAssetParam: %@\n", editor_header->numResAssetParam);
    dumpLine_(buffered_str, "  numResTriggerOverwriteParam: %@\n",
              editor_header->numResTriggerOverwriteParam);
    dumpLine_(buffered_str, "  numLocalPropertyNameRefTable: %@\n",
              editor_header->numLocalPropertyNameRefTable);
    dumpLine_(buffered_str, "  numLocalPropertyEnumNameRefTable: %@\n",
              editor_header->numLocalPropertyEnumNameRefTable);
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
    dumpUserBin_(0, editor_name, editor_resource->pResUserHeader, param_define, buffered_str);
    dumpCommonResourceRear_(editor_resource, bin_accessor, editor_resource->_0, heap, false,
                            buffered_str);
}

// WIP
void ResourceParamCreator::dumpCommonResourceFront_(CommonResourceParam* common_res_param,
                                                    const BinAccessor* bin_accessor,
                                                    bool param_bool1,
                                                    sead::BufferedSafeString* dump_str)
{
    unsigned int all_param_num{0};
    unsigned int not_default_param_num{0};
    unsigned int overwrite_param_num{0};
    u64 asset_param_table_end{(u64)common_res_param->assetParamTable};
    sead::BitFlag64 mask = common_res_param->assetParamTable->mask;

    dumpLine_(dump_str, "<< ResAssetParamTable (addr:0x%x, size:print later) >>\n",
              common_res_param->assetParamTable);
    if (common_res_param->numResAssetParam != 0) {
        if (!param_bool1) {
            for (u32 i{0}; i < common_res_param->numResAssetParam; ++i) {
                u32* raw_values = common_res_param->assetParamTable->rawValues;
                mask = common_res_param->assetParamTable->mask;
                dumpLine_(dump_str, "  [%d] mask: %lu\n", i, mask.getDirect());
                if (bin_accessor->mNumAssetParam != 0) {
                    for (u32 j{0}; j < bin_accessor->mNumAssetParam; ++j) {
                        if (!(mask.getDirect() & 1L << (j & 0x3f)))
                            dumpLine_(dump_str,
                                      "  [%d] param of bit[%d]: not exist(default value)\n", i, j);
                        else {
                            u32 raw_value = *raw_values;
                            dumpLine_(dump_str,
                                      "  [%d] param of bit[%d]: rawValue: %u (referenceType: %d, "
                                      "value: %d)\n",
                                      i, j, raw_value >> 0x18, raw_value & 0xffffff);
                            not_default_param_num += 1;
                            raw_values += sizeof(u32);
                            raw_value += 1;
                        }
                        all_param_num += j;
                    }
                }
                asset_param_table_end = (u64)raw_values;
            }
        }
        else {
            for (u32 i{0}; i < common_res_param->numResAssetParam; ++i) {
                u32* raw_values = common_res_param->assetParamTable->rawValues;
                mask = common_res_param->assetParamTable->mask;
                if (bin_accessor->mNumAssetParam != 0) {
                    for (u32 j{0}; j < bin_accessor->mNumAssetParam; ++j) {
                        if (!(mask.getDirect() & 1L << (j & 0x3f))) {
                            not_default_param_num += 1;
                            raw_values += 1;
                        }
                        all_param_num += j;
                    }
                    asset_param_table_end = (u64)raw_values;
                }
            }
            dumpLine_(dump_str, "  ...no content print.\n");
        }
    }
    else {
        all_param_num = 0;
        not_default_param_num = 0;
    }

    // if (!param_bool1)

    dumpLine_(dump_str,
              "<< ResAssetParamTable finished(size:%d, allParamNum=%d, notDefaultParamNum=%d) >>\n",
              asset_param_table_end - (u64)common_res_param->assetParamTable, all_param_num,
              not_default_param_num);

    u64 trigger_ow_param_table_pos;
    if (bin_accessor->mResourceHeader)
        trigger_ow_param_table_pos = bin_accessor->mResourceHeader->triggerOverwriteParamTablePos;
    else
        trigger_ow_param_table_pos = bin_accessor->mEditorHeader->triggerOverwriteParamTablePos;

    dumpLine_(dump_str, "<< ResTriggerOverwriteParamTable (addr:0x%x, size:print later) >>\n",
              trigger_ow_param_table_pos);

    u64 pos{trigger_ow_param_table_pos};
    u32 ow_param_table_end{0};
    if (common_res_param->numResTriggerOverwriteParam == 0) {
        all_param_num = 0;
        overwrite_param_num = 0;
        ow_param_table_end = common_res_param->triggerOverwriteParamTablePos;
    }
    else if (param_bool1) {
        all_param_num = 0;
        for (u32 i{0}; i < common_res_param->numResTriggerOverwriteParam; ++i) {
            u32* param{solveOffset<u32>(pos)};
            u32 mask = *param;
            dumpLine_(dump_str, "  [%d] mask: %lu\n", i, mask);
            pos += 4;
            param += 1;
            if (bin_accessor->mNumUserParam != 0) {
                for (u32 j{0}; j < bin_accessor->mNumAssetParam; ++j) {
                    if (mask & 1L << (j & 0x3f)) {
                        dumpLine_(dump_str, "  [%d] param of bit[%d]: not exist(not overwritten)\n",
                                  i, j);
                    }
                    else {
                        u32 param_value = *param;
                        dumpLine_(dump_str,
                                  "  [%d] param of bit[%d]: rawValue: %u (referenceType: %d, "
                                  "value: %d)\n",
                                  i, j, param_value >> 0x18, param_value & 0xffffff);
                        overwrite_param_num += 1;
                        pos += 4;
                        param += 1;
                    }
                    all_param_num += j;
                }
            }
            ow_param_table_end = pos;
        }
    }
    else {
        all_param_num = 0;
        u32 param_value = pos + 4;
        u32 k = param_value;
        for (u32 i{0}; common_res_param->numResTriggerOverwriteParam; ++i) {
            if (bin_accessor->mNumUserParam != 0) {
                u32* param_table{solveOffset<u32>(pos)};
                u32 mask = *param_table;
                for (u32 j{0}; j < bin_accessor->mNumUserParam; ++j) {
                    if (mask & 1L << (j & 0x3f)) {
                        overwrite_param_num += 1;
                        k = param_value + 4;
                    }
                    param_value = k;
                    all_param_num += j;
                }
            }
            pos = param_value;
            k = param_value;
        }
    }

    if (!param_bool1)
        dumpLine_(dump_str, "  ...no content print.\n");

    dumpLine_(
        dump_str,
        "<< ResTriggerOverwriteParamTable finished(size:%d, allParamNum=%d, overwriteNum=%d) >>\n",
        ow_param_table_end - pos, all_param_num, overwrite_param_num);
    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< LocalPropertyNameRefTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->localPropertyNameRefTable, 8,
              common_res_param->numLocalPropertyNameRefTable,
              common_res_param->numLocalPropertyNameRefTable * 6);

    if (param_bool1) {
        if (common_res_param->numLocalPropertyNameRefTable != 0) {
            for (u32 i{0}; i < common_res_param->numLocalPropertyNameRefTable; ++i) {
                dumpLine_(dump_str, "  [%d] namePos=%d\n", i,
                          common_res_param->localPropertyNameRefTable[i]);
            }
        }
    }
    else {
        dumpLine_(dump_str, "  ...no content print.\n");
    }
    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< LocalPropertyEnumNameRefTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->localPropertyEnumNameRefTable, 8,
              common_res_param->numLocalPropertyEnumNameRefTable,
              common_res_param->numLocalPropertyEnumNameRefTable * 8);

    if (param_bool1) {
        if (common_res_param->numLocalPropertyEnumNameRefTable != 0) {
            for (u32 i{0}; i < common_res_param->numLocalPropertyEnumNameRefTable; ++i) {
                dumpLine_(dump_str, "  [%d] enumNamePos=%d\n", i,
                          common_res_param->localPropertyEnumNameRefTable[i]);
            }
        }
    }
    else {
        dumpLine_(dump_str, "  ...no content print.\n");
    }
    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< DirectValueTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->directValueTable, 4, common_res_param->numDirectValueTable,
              common_res_param->numDirectValueTable * sizeof(u32));

    if (param_bool1) {
        if (common_res_param->numDirectValueTable != 0) {
            for (u32 i{0}; i < common_res_param->numDirectValueTable; ++i) {
                dumpLine_(dump_str, "  [%d] directvalue=%d\n", i,
                          common_res_param->directValueTable[i]);
            }
        }
    }
    else {
        dumpLine_(dump_str, "  ...no content print.\n");
    }
    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< RandomCallTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->randomCallTable, 8, common_res_param->numRandomTable,
              common_res_param->numRandomTable * 8);

    if (param_bool1) {
        if (common_res_param->numRandomTable != 0) {
            for (u32 i{0}; i < common_res_param->numRandomTable; ++i) {
                dumpLine_(dump_str, "  [%d] minValue=%.4f, maxValue=%.4f\n", i,
                          common_res_param->randomCallTable[i].minValue,
                          common_res_param->randomCallTable[i].maxValue);
            }
        }
    }
    else {
        dumpLine_(dump_str, "  ...no content print.\n");
    }
    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< CurveCallTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->curveCallTable, 14, common_res_param->numCurveTable,
              common_res_param->numCurveTable * sizeof(ResCurveCallTable));

    if (param_bool1) {
        if (common_res_param->numCurveTable != 0) {
            for (u32 i{0}; i < common_res_param->numCurveTable; ++i) {
                dumpLine_(dump_str, "  [%d].curvePointStartPos: %hu\n", i,
                          common_res_param->curveCallTable[i].curvePointStartPos);
                dumpLine_(dump_str, "  [%d].numPoint: %hu\n", i,
                          common_res_param->curveCallTable[i].numPoint);
                dumpLine_(dump_str, "  [%d].curveType: %hu\n", i,
                          common_res_param->curveCallTable[i].curveType);
                dumpLine_(dump_str, "  [%d].isPropGlobal: %hu\n", i,
                          common_res_param->curveCallTable[i].isPropGlobal);
                dumpLine_(dump_str, "  [%d].propName: %u\n", i,
                          common_res_param->curveCallTable[i].propName);
                dumpLine_(dump_str, "  [%d].propIdx: %d\n", i,
                          common_res_param->curveCallTable[i].propIdx);
                dumpLine_(dump_str, "  [%d].localPropertyNameIdx: %hd\n", i,
                          common_res_param->curveCallTable[i].localPropertyNameIdx);
            }
        }
    }
    else {
        dumpLine_(dump_str, "  ...no content print.\n");
    }
    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< CurvePointTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->curvePointTable, 8, common_res_param->numCurvePointTable,
              common_res_param->numCurvePointTable * 8);

    if (param_bool1) {
        if (common_res_param->numCurvePointTable != 0) {
            for (u32 i{0}; i < common_res_param->numCurvePointTable; ++i) {
                dumpLine_(dump_str, "  [%d] x=%.4f, y=%.4f\n", i,
                          common_res_param->curvePointTable[i].x,
                          common_res_param->curvePointTable[i].y);
            }
        }
    }
    else {
        dumpLine_(dump_str, "  ...no content print.\n");
    }
    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< ExRegion (addr:0x%x, size:unknown) >>\n",
              common_res_param->exRegionPos);

    if (param_bool1)
        dumpLine_(dump_str, "  ...not dump content.\n");
    else
        dumpLine_(dump_str, "  ...no content print.\n");

    dumpLine_(dump_str, "\n");
};

// WIP
void ResourceParamCreator::dumpUserBin_(u32 p1, const sead::SafeString& user_name,
                                        ResUserHeader* user_header,
                                        const ParamDefineTable* param_define,
                                        sead::BufferedSafeString* buffered_str)
{
    // ------------------------------------- ResUserHeader -----------------------------------------
    dumpLine_(buffered_str, "<< ResUserHeader[%d] (addr:0x%x, name=%s) >>\n", p1, user_header,
              user_name.cstr());
    dumpLine_(buffered_str, "    isSetup: %u\n", user_header->isSetup);
    dumpLine_(buffered_str, "    numLocalProperty: %u\n", user_header->numLocalProperty);
    dumpLine_(buffered_str, "    numCallTable: %u\n", user_header->numCallTable);
    dumpLine_(buffered_str, "    numAsset: %u\n", user_header->numAsset);
    dumpLine_(buffered_str, "    numRandomContainer2: %u\n", user_header->numRandomContainer2);
    dumpLine_(buffered_str, "    numResActionSlot: %u\n", user_header->numResActionSlot);
    dumpLine_(buffered_str, "    numResAction: %u\n", user_header->numResAction);
    dumpLine_(buffered_str, "    numResActionTrigger: %u\n", user_header->numResActionTrigger);
    dumpLine_(buffered_str, "    numResProperty: %u\n", user_header->numResProperty);
    dumpLine_(buffered_str, "    numResPropertyTrigger: %u\n", user_header->numResPropertyTrigger);
    dumpLine_(buffered_str, "    numResAlwaysTrigger: %u\n", user_header->numResAlwaysTrigger);
    dumpLine_(buffered_str, "    triggerTablePos: %u\n", user_header->triggerTablePos);
    dumpLine_(buffered_str, "\n");

    u64 pos{(u64)user_header + 1};

    // ------------------------------- LocalPropertyNameRefTable -----------------------------------
    dumpLine_(buffered_str, "    << LocalPropertyNameRefTable (addr:0x%x, num=%d) >>\n", pos,
              user_header->numLocalProperty);
    if (user_header->numLocalProperty != 0)
        for (int i{0}; i < user_header->numLocalProperty; ++i)
            dumpLine_(buffered_str, "        [%d]: namePos=%d\n", pos + i * sizeof(u32));
    dumpLine_(buffered_str, "\n");

    // --------------------------------------- UserParamTable --------------------------------------
    u32 num_property{user_header->numLocalProperty};
    u32 user_param_num{param_define->getNumUserParam()};
    u64 pos2{pos + num_property * sizeof(u32)};
    dumpLine_(buffered_str, "    << UserParamTable (addr:0x%x, num=%d) >>\n", pos2, user_param_num);

    if (user_param_num != 0) {
        for (int i{0}; i < user_param_num; ++i) {
            // TODO: This looks weird. Take a look later
            u32* raw_value{&user_header->triggerTablePos};
            raw_value = &raw_value[num_property + i];
            dumpLine_(buffered_str, "        [%d] rawValue: %u (type: %d, value: %d)\n",
                      i & 0xffffffff, *raw_value >> 0x18, *raw_value & 0xffffff);
        }
    }
    dumpLine_(buffered_str, "\n");

    // ------------------------------------- SortedAssetIdTable ------------------------------------
    pos2 += user_param_num * sizeof(u32);
    dumpLine_(buffered_str, "    << SortedAssetIdTable (addr:0x%x, num=%d) >>\n", pos2,
              user_header->numCallTable);
    if (user_header->numCallTable != 0)
        for (int i{0}; i < user_header->numCallTable; ++i)
            dumpLine_(buffered_str, "        [%d]: %hu\n", i, pos2 + i * sizeof(u16));
    dumpLine_(buffered_str, "\n");

    // --------------------------------------- AssetCallTable --------------------------------------
    pos2 += user_header->numCallTable * sizeof(u16);
    if ((user_header->numCallTable & 1) != 0)
        pos2 += 2;
    dumpLine_(buffered_str, "    << AssetCallTable (addr:0x%x, num=%d) >>\n", pos2);
    if (user_header->numCallTable != 0) {
        for (int i{0}; i < user_header->numCallTable; ++i) {
            ResAssetCallTable* asset_call_table{
                (ResAssetCallTable*)(pos2 + i * sizeof(ResAssetCallTable))};
            dumpLine_(buffered_str, "        [%d].keyNamePos: %u\n", i,
                      asset_call_table->keyNamePos);
            dumpLine_(buffered_str, "        [%d].assetId: %hd\n", i, asset_call_table->assetId);
            dumpLine_(buffered_str, "        [%d].flag: %hu\n", i, asset_call_table->flag);
            dumpLine_(buffered_str, "        [%d].parentIndex: %d\n", i,
                      asset_call_table->parentIndex);
            dumpLine_(buffered_str, "        [%d].paramStartPos: %u\n", i,
                      asset_call_table->paramStartPos);
            dumpLine_(buffered_str, "        [%d].conditionPos: %u\n", i,
                      asset_call_table->conditionPos);
        }
    }
    dumpLine_(buffered_str, "\n");

    // --------------------------------------- ContainerTable --------------------------------------
    ResContainerParam* container_param{
        (ResContainerParam*)(pos2 + user_header->numCallTable * sizeof(ResAssetCallTable))};
    u32 num_container{user_header->numCallTable - user_header->numAsset};
    dumpLine_(buffered_str, "    << ContainerTable (addr:0x%x, num=%d) >>\n", container_param,
              num_container);
    if (num_container != 0) {
        for (int i{0}; i < num_container; ++i) {
            if (container_param->type == ContainerType::Switch) {
                dumpLine_(buffered_str, "        [%d].type: %d\n", i, container_param->type);
                dumpLine_(buffered_str, "        [%d].childrenStartIndex: %d\n", i,
                          container_param->childrenStartIndex);
                dumpLine_(buffered_str, "        [%d].childrenEndIndex: %d\n", i,
                          container_param->childrenEndIndex);
                dumpLine_(buffered_str, "        [%d].watchPropertyNamePos: %u\n", i,
                          container_param->watchPropertyNamePos);
                dumpLine_(buffered_str, "        [%d].watchPropertyId: %d\n", i,
                          container_param->watchPropertyId);
                dumpLine_(buffered_str, "        [%d].localPropertyNameIdx: %hd\n", i,
                          container_param->localPropertyNameIdx);
                dumpLine_(buffered_str, "        [%d].isGlobal: %d\n", i,
                          container_param->isGlobal);
                container_param += 1;
            }
            else {
                dumpLine_(buffered_str, "        [%d].type: %d\n", i, container_param->type);
                dumpLine_(buffered_str, "        [%d].childrenStartIndex: %d\n", i,
                          container_param->childrenStartIndex);
                dumpLine_(buffered_str, "        [%d].childrenEndIndex: %d\n", i,
                          container_param->childrenEndIndex);
                container_param = (ResContainerParam*)container_param->watchPropertyNamePos;
            }
        }
    }
    dumpLine_(buffered_str, "\n");

    // ------------------------------------- ResActionSlotTable ------------------------------------
    u64 action_slot_table_abs_pos{user_header->triggerTablePos + (u64)user_header};
    u64 pos3{action_slot_table_abs_pos | sMinAddressHigh};
    if (action_slot_table_abs_pos < sMinAddressLow)
        pos3 += 0x100000000;

    dumpLine_(buffered_str, "    << ResActionSlotTable (addr:0x%x, num=%d) >>\n", pos3,
              user_header->numResActionSlot);
    if (user_header->numResActionSlot != 0) {
        ResActionSlot* action_slot;
        for (int i{0}; i < user_header->numResActionSlot; ++i) {
            action_slot = (ResActionSlot*)(pos3 + i * sizeof(ResActionSlot));
            dumpLine_(buffered_str,
                      "        [%d] namePos: %u, actionStartIdx: %hd, actionEndIdx: %hd\n", i,
                      action_slot->namePos, action_slot->actionStartIdx, action_slot->actionEndIdx);
        }
    }
    dumpLine_(buffered_str, "\n");
    pos2 = pos3 + user_header->numResActionSlot * sizeof(ResActionSlot);

    // --------------------------------------- ResActionTable --------------------------------------
    dumpLine_(buffered_str, "    << ResActionTable (addr:0x%x, num=%d) >>\n", pos2,
              user_header->numResAction);
    if (user_header->numResAction != 0) {
        ResAction* res_action;
        for (int i{0}; i < user_header->numResAction; ++i) {
            res_action = (ResAction*)(pos2 + i * sizeof(ResAction));
            dumpLine_(buffered_str,
                      "        [%d] namePos: %u, triggerStartIdx: %d, triggerEndIdx: %d\n", i,
                      res_action->namePos, res_action->triggerStartIdx, res_action->triggerEndIdx);
        }
    }
    dumpLine_(buffered_str, "\n");
    pos2 += user_header->numResAction * sizeof(ResAction);

    // ----------------------------------- ResActionTriggerTable ----------------------------------
    dumpLine_(buffered_str, "    << ResActionTriggerTable (addr:0x%x, num=%d) >>\n", pos2,
              user_header->numResActionTrigger);
    if (user_header->numResActionTrigger != 0) {
        ResActionTrigger* res_action_trigger;
        for (int i{0}; i < user_header->numResActionTrigger; ++i) {
            res_action_trigger = (ResActionTrigger*)(pos2 + i * sizeof(ResActionTrigger));
            dumpLine_(buffered_str, "        [%d].guId: %d\n", i, res_action_trigger->guId);
            dumpLine_(buffered_str, "        [%d].assetCtbPos: %u\n", i,
                      res_action_trigger->assetCtbPos);
            dumpLine_(buffered_str, "        [%d].startFrame: %d\n", i,
                      res_action_trigger->startFrame);
            dumpLine_(buffered_str, "        [%d].endFrame: %d\n", i, res_action_trigger->endFrame);
            dumpLine_(buffered_str, "        [%d].flag: %hu\n", i, res_action_trigger->flag);
            dumpLine_(buffered_str, "        [%d].overwriteHash: %hd\n", i,
                      res_action_trigger->overwriteHash);
            dumpLine_(buffered_str, "        [%d].overwriteParamPos: %u\n", i,
                      res_action_trigger->overwriteParamPos);
        }
    }
    dumpLine_(buffered_str, "\n");
    pos2 += user_header->numResActionTrigger * sizeof(ResActionTrigger);

    // -------------------------------------- ResPropertyTable -------------------------------------
    dumpLine_(buffered_str, "    << ResPropertyTable (addr:0x%x, num=%d) >>\n", pos2,
              user_header->numResProperty);
    if (user_header->numResProperty != 0) {
        ResProperty* res_property;
        for (int i{0}; i < user_header->numResProperty; ++i) {
            res_property = (ResProperty*)(pos2 + i * sizeof(ResProperty));
            dumpLine_(buffered_str,
                      "        [%d] watchPropertyNamePos: %u, isGlobal: %d, triggerStartIdx: %d, "
                      "triggerEndIdx: %d\n",
                      i, res_property->watchPropertyNamePos, res_property->isGlobal,
                      res_property->triggerStartIdx, res_property->triggerEndIdx);
        }
    }
    dumpLine_(buffered_str, "\n");
    pos2 += user_header->numResProperty * sizeof(ResProperty);

    // ---------------------------------- ResPropertyTriggerTable ---------------------------------
    dumpLine_(buffered_str, "    << ResPropertyTriggerTable (addr:0x%x, num=%d) >>\n", pos2,
              user_header->numResPropertyTrigger);
    if (user_header->numResPropertyTrigger != 0) {
        ResPropertyTrigger* res_property_trigger;
        for (int i{0}; i < user_header->numResPropertyTrigger; ++i) {
            res_property_trigger = (ResPropertyTrigger*)(pos3 + i * sizeof(ResPropertyTrigger));
            dumpLine_(buffered_str, "        [%d].guId: %d\n", i, res_property_trigger->guId);
            dumpLine_(buffered_str, "        [%d].assetCtbPos: %u\n", i,
                      res_property_trigger->assetCtbPos);
            dumpLine_(buffered_str, "        [%d].condition: %u\n", i,
                      res_property_trigger->condition);
            dumpLine_(buffered_str, "        [%d].flag: %hu\n", i, res_property_trigger->flag);
            dumpLine_(buffered_str, "        [%d].overwriteHash: %hd\n", i,
                      res_property_trigger->overwriteHash);
            dumpLine_(buffered_str, "        [%d].overwriteParamPos: %u\n", i,
                      res_property_trigger->overwriteParamPos);
        }
    }
    dumpLine_(buffered_str, "\n");
    pos2 += user_header->numResPropertyTrigger * sizeof(ResPropertyTrigger);

    // ----------------------------------- ResAlwaysTriggerTable ----------------------------------
    dumpLine_(buffered_str, "    << ResAlwaysTriggerTable (addr:0x%x, num=%d) >>\n", pos2,
              user_header->numResAlwaysTrigger);
    if (user_header->numResAlwaysTrigger != 0) {
        ResAlwaysTrigger* res_always_trigger;
        for (int i{0}; i < user_header->numResAlwaysTrigger; ++i) {
            res_always_trigger = (ResAlwaysTrigger*)(pos2 + i * sizeof(ResAlwaysTrigger));
            dumpLine_(buffered_str, "        [%d].guId: %d\n", res_always_trigger->guId);
            dumpLine_(buffered_str, "        [%d].assetCtbPos: %u\n",
                      res_always_trigger->assetCtbPos);
            dumpLine_(buffered_str, "        [%d].flag: %hu\n", res_always_trigger->flag);
            dumpLine_(buffered_str, "        [%d].overwriteHash: %hd\n",
                      res_always_trigger->overwriteHash);
            dumpLine_(buffered_str, "        [%d].overwriteParamPos: %u\n",
                      res_always_trigger->overwriteParamPos);
        }
    }
    dumpLine_(buffered_str, "\n");
};

// WIP
void ResourceParamCreator::dumpCommonResourceRear_(CommonResourceParam* common_res_param,
                                                   const BinAccessor* bin_accessor, u32 p1,
                                                   sead::Heap* heap, bool p2,
                                                   sead::BufferedSafeString* buffered_str)
{
    // --------------------------------------- ConditionTable --------------------------------------
    dumpLine_(buffered_str, "<< ConditionTable (addr:0x%x, size:%d) >>\n",
              common_res_param->conditionTablePos,
              common_res_param->nameTablePos - common_res_param->conditionTablePos, p2);

    u32 pos1{common_res_param->conditionTablePos};
    u32 condition_size;
    ResCondition* res_condition;
    for (int i{0}; pos1 < common_res_param->nameTablePos; ++i) {
        res_condition = (ResCondition*)(sMinAddressHigh | pos1);
        if (pos1 < sMinAddressLow)
            res_condition += 0x40000000;

        if (res_condition->parentContainerType < ContainerType::Random2) {
            RandomCondition* condition{(RandomCondition*)res_condition};
            dumpLine_(buffered_str, "  [%d].parentContainerType: %d\n", i,
                      condition->parentContainerType);
            dumpLine_(buffered_str, "  [%d].weight: %.4f\n", i, condition->weight);
            condition_size = sizeof(RandomCondition);
        }
        else {
            condition_size = 0;
            if (res_condition->parentContainerType == ContainerType::Switch) {
                dumpLine_(buffered_str, "  [%d].parentContainerType: %d\n", i,
                          res_condition->parentContainerType);
                dumpLine_(buffered_str, "  [%d].propertyType: %d\n", i,
                          res_condition->propertyType);
                dumpLine_(buffered_str, "  [%d].compareType: %d\n", i, res_condition->compareType);
                dumpLine_(buffered_str, "  [%d].value: %d\n", i, res_condition->value);
                dumpLine_(buffered_str, "  [%d].localPropertyEnumNameIdx: %d\n", i,
                          res_condition->localPropertyEnumNameIdx);
                dumpLine_(buffered_str, "  [%d].isSolved: %d\n", i, res_condition->isSolved);
                dumpLine_(buffered_str, "  [%d].isGlobal: %d\n", i, res_condition->isGlobal);
                condition_size = sizeof(ResCondition);
            }
        }
        pos1 += condition_size;
    }
    dumpLine_(buffered_str, "\n");

    // ----------------------------------------- NameTable -----------------------------------------
    u32* name_table_pos;
    if (!bin_accessor->mResourceHeader)
        name_table_pos = &bin_accessor->mEditorHeader->nameTablePos;
    else
        name_table_pos = &bin_accessor->mResourceHeader->nameTablePos;

    u32 name_table_size = p1 - *name_table_pos;

    dumpLine_(buffered_str, "<< NameTable (addr:0x%x, size:%d) >>\n",
              common_res_param->nameTablePos, name_table_size);
    if (name_table_size != 0) {
        char* dest = new (heap, 8) char;
        char* src = (char*)(sMinAddressHigh | common_res_param->nameTablePos);
        if (common_res_param->nameTablePos < sMinAddressLow)
            src += 0x100000000;
        memcpy(dest, src, name_table_size);
        pos1 = name_table_size - 1;
        if (pos1 == 0) {
            u32 ivar3{0};
            dumpLine_(buffered_str, "  {%s}\n", dest);
            if (!dest) {
                dumpLine_(buffered_str, "\n");
                return;
            }
            if (p1 - 2 == *name_table_pos)
                ivar3 = 0;
            else {
                do {
                    if (dest[ivar3] == '\0')
                        dest[ivar3] = ' ';
                    if (dest[ivar3 + 1] == '\0')
                        dest[ivar3 + 1] = ' ';
                    ivar3 += 2;
                } while (pos1 - (pos1 & 1) != ivar3);
                if ((pos1 & 1) != 0 && dest[ivar3] == '\0')
                    dest[ivar3] = ' ';
                dumpLine_(buffered_str, "  {%s}\n", dest);
            }

            delete dest;
            return;
        }
    }
};
}  // namespace xlink2