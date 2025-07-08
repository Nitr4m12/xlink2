#include <cstddef>

#include "prim/seadBitFlag.h"
#include "prim/seadSafeString.h"
#include "xlink2/xlink2Condition.h"
#include "xlink2/xlink2ResContainerParam.h"
#include "xlink2/xlink2ResourceParamCreator.h"
#include "xlink2/xlink2ResParam.h"
#include "xlink2/xlink2ResUserHeader.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
// NON-MATCHING
ResourceParamCreator::BinAccessor::BinAccessor(ResourceHeader* res_header,
                                               ParamDefineTable const* param_define)
{
    resourceHeader = res_header;
    editorHeader = nullptr;
    binStart = (long)res_header;
    auto num_user = resourceHeader->numUser * 8;
    auto num_user_params = param_define->getSize();
    assetsStart = binStart + num_user + num_user_params + sizeof(ResourceHeader);
    numTriggerParam = param_define->get0();
    numAssetParam = param_define->getNumAssetParam();
}

ResourceParamCreator::BinAccessor::BinAccessor(EditorHeader* editor_header,
                                               ParamDefineTable const* param_define)
{
    resourceHeader = nullptr;
    editorHeader = editor_header;
    binStart = (long)editor_header;
    assetsStart = (long)editor_header + sizeof(EditorHeader);
    numTriggerParam = param_define->get0();
    numAssetParam = param_define->getNumAssetParam();
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

    common_res_param->numResParam = bin_accessor->resourceHeader ?
                                        bin_accessor->resourceHeader->numResParam :
                                        bin_accessor->editorHeader->numResParam;
    common_res_param->numResAssetParam = bin_accessor->resourceHeader ?
                                             bin_accessor->resourceHeader->numResAssetParam :
                                             bin_accessor->editorHeader->numResAssetParam;
    common_res_param->numResTriggerOverwriteParam =
        bin_accessor->resourceHeader ? bin_accessor->resourceHeader->numResTriggerOverwriteParam :
                                        bin_accessor->editorHeader->numResTriggerOverwriteParam;
    common_res_param->numLocalPropertyNameRefTable =
        bin_accessor->resourceHeader ?
            bin_accessor->resourceHeader->numLocalPropertyNameRefTable :
            bin_accessor->editorHeader->numLocalPropertyNameRefTable;
    common_res_param->numLocalPropertyEnumNameRefTable =
        bin_accessor->resourceHeader ?
            bin_accessor->resourceHeader->numLocalPropertyEnumNameRefTable :
            bin_accessor->editorHeader->numLocalPropertyEnumNameRefTable;
    common_res_param->numDirectValueTable = bin_accessor->resourceHeader ?
                                                bin_accessor->resourceHeader->numDirectValueTable :
                                                bin_accessor->editorHeader->numDirectValueTable;
    common_res_param->numRandomTable = bin_accessor->resourceHeader ?
                                           bin_accessor->resourceHeader->numRandomTable :
                                           bin_accessor->editorHeader->numRandomTable;
    common_res_param->numCurveTable = bin_accessor->resourceHeader ?
                                          bin_accessor->resourceHeader->numCurveTable :
                                          bin_accessor->editorHeader->numCurveTable;
    common_res_param->numCurvePointTable = bin_accessor->resourceHeader ?
                                               bin_accessor->resourceHeader->numCurvePointTable :
                                               bin_accessor->editorHeader->numCurvePointTable;

    if (common_res_param->numResAssetParam > 0)
        common_res_param->assetParamTable =
            calcOffset<ResAssetParam>(bin_accessor->assetsStart);

    common_res_param->triggerOverwriteParamTablePos =
        bin_accessor->resourceHeader ?
            bin_accessor->resourceHeader->triggerOverwriteParamTablePos :
            bin_accessor->editorHeader->triggerOverwriteParamTablePos;
    if (common_res_param->numResTriggerOverwriteParam > 0)
        common_res_param->triggerOverwriteParamTablePos += bin_accessor->binStart;

    if (bin_accessor->resourceHeader)
        ptr = &bin_accessor->resourceHeader->localPropertyNameRefTablePos;
    else
        ptr = &bin_accessor->editorHeader->localPropertyNameRefTablePos;
    auto* local_property_name_ref_table = calcOffset<u32>(bin_accessor->binStart + *ptr);
    if (common_res_param->numLocalPropertyNameRefTable > 0)
        common_res_param->localPropertyNameRefTable = local_property_name_ref_table;

    ptr = common_res_param->localPropertyNameRefTable +
          common_res_param->numLocalPropertyNameRefTable;
    if (common_res_param->numLocalPropertyEnumNameRefTable > 0)
        common_res_param->localPropertyEnumNameRefTable = ptr;
    ptr = ptr + common_res_param->numLocalPropertyEnumNameRefTable;

    if (common_res_param->numDirectValueTable > 0)
        common_res_param->directValueTable = (s32*)ptr;
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

    if (bin_accessor->resourceHeader)
        ptr = &bin_accessor->resourceHeader->exRegionPos;
    else
        ptr = &bin_accessor->editorHeader->exDataRegionPos;
    common_res_param->exRegionPos = *ptr + bin_accessor->binStart;

    if (bin_accessor->resourceHeader)
        ptr = &bin_accessor->resourceHeader->conditionTablePos;
    else
        ptr = &bin_accessor->editorHeader->conditionTablePos;
    common_res_param->conditionTablePos = *ptr + bin_accessor->binStart;

    if (bin_accessor->resourceHeader)
        ptr = &bin_accessor->resourceHeader->nameTablePos;
    else
        ptr = &bin_accessor->editorHeader->nameTablePos;
    common_res_param->nameTablePos = *ptr + bin_accessor->binStart;
}

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

    dumpLine_(buffered_str, "<< ParamDefineTable (addr:0x%x, size:%@) >>\n", reinterpret_cast<u64>(rom_res->offsetTable) + offset_table_size,
              param_define->getSize());
    dumpLine_(buffered_str, "  ...no content print.\n\n");

    dumpCommonResourceFront_(rom_res, bin_accessor, p1, buffered_str);
    if (p1 && res_header->numUser != 0) {
        for (u32 i{0}; i < res_header->numUser; ++i) {
            u64 user_offset = rom_res->offsetTable[i] + bin_accessor->binStart;
            auto* user_header = reinterpret_cast<ResUserHeader*>((user_offset >= sMinAddressLow) ? 
                                        (user_offset | sMinAddressHigh) :
                                        (user_offset | sMinAddressHigh) + 0x100000000);
            dumpUserBin_(i, "", user_header, param_define,
                         buffered_str);
        }
    }
    dumpCommonResourceRear_(rom_res, bin_accessor, res_header->dataSize, heap, false, buffered_str);
}

void ResourceParamCreator::dumpEditorResource_(EditorResourceParam* editor_resource,
                                               const BinAccessor* bin_accessor,
                                               const ParamDefineTable* param_define,
                                               sead::Heap* heap)
{
    dumpLine_(nullptr, "[XLink2] EditorBuffer dump\n");

    EditorHeader* editor_header{editor_resource->pEditorHeader};
    sead::FixedSafeString<64>* editor_name{&editor_resource->editorName};

    dumpLine_(nullptr, "<< EditorHeader[%s] (addr:0x%x, size:%@) >>\n",
              editor_resource->editorName.getBuffer(), editor_header, sizeof(EditorHeader));
    dumpLine_(nullptr, "  numResParam: %@\n", editor_header->numResParam);
    dumpLine_(nullptr, "  numResAssetParam: %@\n", editor_header->numResAssetParam);
    dumpLine_(nullptr, "  numResTriggerOverwriteParam: %@\n",
              editor_header->numResTriggerOverwriteParam);
    dumpLine_(nullptr, "  numLocalPropertyNameRefTable: %@\n",
              editor_header->numLocalPropertyNameRefTable);
    dumpLine_(nullptr, "  numLocalPropertyEnumNameRefTable: %@\n",
              editor_header->numLocalPropertyEnumNameRefTable);
    dumpLine_(nullptr, "  numDirectValueTable: %@\n", editor_header->numDirectValueTable);
    dumpLine_(nullptr, "  numRandomTable: %@\n", editor_header->numRandomTable);
    dumpLine_(nullptr, "  numCurveTable: %@\n", editor_header->numCurveTable);
    dumpLine_(nullptr, "  numCurvePointTable: %@\n", editor_header->numCurvePointTable);
    dumpLine_(nullptr, "  exDataRegionPos: %@\n", editor_header->exDataRegionPos);
    dumpLine_(nullptr, "  userNamePos: %@\n", editor_header->userNamePos);
    dumpLine_(nullptr, "  userBinPos: %@\n", editor_header->userBinPos);
    dumpLine_(nullptr, "  conditionTablePos: %@\n", editor_header->conditionTablePos);
    dumpLine_(nullptr, "  nameTablePos: %@\n", editor_header->nameTablePos);
    dumpLine_(nullptr, "\n");

    dumpCommonResourceFront_(editor_resource, bin_accessor, true, nullptr);
    dumpUserBin_(0, *editor_name, editor_resource->pResUserHeader, param_define, nullptr);
    dumpCommonResourceRear_(editor_resource, bin_accessor, editor_resource->_0, heap, false,
                            nullptr);
}

// WIP
void ResourceParamCreator::dumpCommonResourceFront_(CommonResourceParam* common_res_param,
                                                    const BinAccessor* bin_accessor,
                                                    bool param_bool1,
                                                    sead::BufferedSafeString* dump_str)
{
    ResAssetParam* asset_param_table_start {common_res_param->assetParamTable};
    dumpLine_(dump_str, "<< ResAssetParamTable (addr:0x%x, size:print later) >>\n", 
            reinterpret_cast<u64>(asset_param_table_start));

    s32 all_param_num {0};
    s32 not_default_param_num {0};
    
    u64 asset_param_table_pos {reinterpret_cast<u64>(common_res_param->assetParamTable)};

    if (common_res_param->numResAssetParam == 0) {
        all_param_num = 0;
        not_default_param_num = 0;
    }
    else if (param_bool1) {
        for (s32 i {0}; i < common_res_param->numResAssetParam; ++i) {
            sead::BitFlag64* mask {reinterpret_cast<sead::BitFlag64*>(asset_param_table_pos)};
            dumpLine_(dump_str, "  [%d] mask: %lu\n", i, mask->getDirect());
            
            asset_param_table_pos += 8;
            
            s32 j {0};
            while (j < bin_accessor->numAssetParam) {
                ResParam* param {reinterpret_cast<ResParam*>(asset_param_table_pos)};
                if (mask->isOnBit(j)) {
                    dumpLine_(dump_str, "  [%d] param of bit[%d]: rawValue: %u (referenceType: %d, value: %d)\n", i, j, 
                            param->rawValue, param->getRefType(), param->getValue());
                    // ++param;
                    ++not_default_param_num;
                    asset_param_table_pos += 4;
                }
                else {
                    dumpLine_(dump_str, "  [%d] param of bit[%d]: not exist(default value)\n", i, j);
                }
                ++j;
            }
            all_param_num += j;
        }
    }
    else {
        for (s32 i {0}; i < common_res_param->numResAssetParam; ++i) {
            sead::BitFlag64* mask {reinterpret_cast<sead::BitFlag64*>(asset_param_table_pos)};
            asset_param_table_pos += 8;
            s32 j {0};
            while (j < bin_accessor->numAssetParam) {
                if (mask->isOnBit(j)) {
                    ++not_default_param_num;
                    asset_param_table_pos += 4;
                }
                ++j;
            }
            all_param_num += j;
        }
    }

    if (!param_bool1)
        dumpLine_(dump_str, "  ...no content print.\n");

    dumpLine_(dump_str,
              "<< ResAssetParamTable finished(size:%d, allParamNum=%d, notDefaultParamNum=%d) >>\n",
              asset_param_table_pos - reinterpret_cast<u64>(asset_param_table_start), all_param_num, not_default_param_num);
    dumpLine_(dump_str, "\n");

    all_param_num = 0;
    u32 overwrite_param_num {0};
    u32 ow_param_table_pos;
    if (bin_accessor->resourceHeader != nullptr)
        ow_param_table_pos = bin_accessor->resourceHeader->triggerOverwriteParamTablePos;
    else
        ow_param_table_pos = bin_accessor->editorHeader->triggerOverwriteParamTablePos;

    dumpLine_(dump_str, "<< ResTriggerOverwriteParamTable (addr:0x%x, size:print later) >>\n",
              ow_param_table_pos);

    ow_param_table_pos = common_res_param->triggerOverwriteParamTablePos;
    if (common_res_param->numResTriggerOverwriteParam == 0) {
        overwrite_param_num = 0;
        all_param_num = 0;
    }
    else if (param_bool1) {
        for (s32 i {0}; i < common_res_param->numResTriggerOverwriteParam; ++i) {
            sead::BitFlag32* mask {reinterpret_cast<sead::BitFlag32*>(calcOffset<u8>(ow_param_table_pos))};
            dumpLine_(dump_str, "  [%d] mask: %lu\n", i, mask->getDirect());
            
            ResParam* param {reinterpret_cast<ResParam*>(mask + 1)};
            ow_param_table_pos += 4;

            s32 j {0};
            while (j < bin_accessor->numTriggerParam) {
                if (mask->isOnBit(j)) {
                    dumpLine_(dump_str, "  [%d] param of bit[%d]: rawValue: %u (referenceType: %d, value: %d)\n", i, j, 
                            param->rawValue, param->getValue(), param->getRefType());
                    ++overwrite_param_num;
                    ++param;
                    ow_param_table_pos += 4;
                }
                else {
                        dumpLine_(dump_str, "  [%d] param of bit[%d]: not exist(not overwritten)\n", i, j);
                }
                ++j;
            }
            all_param_num += j;
        }
    }
    else {
        for (s32 i {0}; i < common_res_param->numResTriggerOverwriteParam; ++i) {
            sead::BitFlag32* mask {reinterpret_cast<sead::BitFlag32*>(calcOffset<u8>(ow_param_table_pos))};
            ow_param_table_pos += 4;
            
            s32 j {0};
            while (j < bin_accessor->numTriggerParam) {
                if (mask->isOnBit(j)) {
                    ++overwrite_param_num;
                    ow_param_table_pos += 4;
                }
                ++j;
            }

            all_param_num += j;
        }
    }

    if (!param_bool1)
        dumpLine_(dump_str, "  ...no content print.\n");

    dumpLine_(
        dump_str,
        "<< ResTriggerOverwriteParamTable finished(size:%d, allParamNum=%d, overwriteNum=%d) >>\n",
        ow_param_table_pos - common_res_param->triggerOverwriteParamTablePos, all_param_num, overwrite_param_num);
    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< LocalPropertyNameRefTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->localPropertyNameRefTable, 8,
              common_res_param->numLocalPropertyNameRefTable,
              common_res_param->numLocalPropertyNameRefTable * 8);

    if (param_bool1) {
        for (u32 i{0}; i < common_res_param->numLocalPropertyNameRefTable; ++i) {
            dumpLine_(dump_str, "  [%d] namePos=%d\n", i,
                        common_res_param->localPropertyNameRefTable[i]);
        }
    }
    else
        dumpLine_(dump_str, "  ...no content print.\n");

    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< LocalPropertyEnumNameRefTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->localPropertyEnumNameRefTable, 8,
              common_res_param->numLocalPropertyEnumNameRefTable,
              common_res_param->numLocalPropertyEnumNameRefTable * 8);

    if (param_bool1) {
        for (u32 i{0}; i < common_res_param->numLocalPropertyEnumNameRefTable; ++i) {
            dumpLine_(dump_str, "  [%d] enumNamePos=%d\n", i,
                        common_res_param->localPropertyEnumNameRefTable[i]);
        }
    }
    else
        dumpLine_(dump_str, "  ...no content print.\n");
    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< DirectValueTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->directValueTable, sizeof(u32), common_res_param->numDirectValueTable,
              common_res_param->numDirectValueTable * sizeof(u32));

    if (param_bool1) {
        for (u32 i{0}; i < common_res_param->numDirectValueTable; ++i) {
            dumpLine_(dump_str, "  [%d] directvalue=%d\n", i,
                        common_res_param->directValueTable[i]);
        }
    }
    else {
        dumpLine_(dump_str, "  ...no content print.\n");
    }
    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< RandomCallTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->randomCallTable, sizeof(ResRandomCallTable), common_res_param->numRandomTable,
              common_res_param->numRandomTable * sizeof(ResRandomCallTable));

    if (param_bool1) {
        for (u32 i{0}; i < common_res_param->numRandomTable; ++i) {
            dumpLine_(dump_str, "  [%d] minValue=%.4f, maxValue=%.4f\n", i,
                        common_res_param->randomCallTable[i].minValue,
                        common_res_param->randomCallTable[i].maxValue);
        }
    }
    else
        dumpLine_(dump_str, "  ...no content print.\n");
    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< CurveCallTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->curveCallTable, common_res_param->numCurveTable, sizeof(ResCurveCallTable),
              common_res_param->numCurveTable * sizeof(ResCurveCallTable));

    if (param_bool1) {
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
    else
        dumpLine_(dump_str, "  ...no content print.\n");
    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< CurvePointTable (addr:0x%x, size:%d*%u=%u) >>\n",
              reinterpret_cast<u64>(common_res_param->curvePointTable), 8, common_res_param->numCurvePointTable,
              common_res_param->numCurvePointTable * 8);

    if (param_bool1) {
        for (u32 i{0}; i < common_res_param->numCurvePointTable; ++i) {
            dumpLine_(dump_str, "  [%d] x=%.4f, y=%.4f\n", i,
                        common_res_param->curvePointTable[i].x,
                        common_res_param->curvePointTable[i].y);
        }
    }
    else
        dumpLine_(dump_str, "  ...no content print.\n");
    dumpLine_(dump_str, "\n");

    dumpLine_(dump_str, "<< ExRegion (addr:0x%x, size:unknown) >>\n",
              common_res_param->exRegionPos);

    if (param_bool1)
        dumpLine_(dump_str, "  ...not dump content.\n");
    else
        dumpLine_(dump_str, "  ...no content print.\n");

    dumpLine_(dump_str, "\n");
}

void ResourceParamCreator::dumpUserBin_(u32 user_index, const sead::SafeString& user_name,
                                        ResUserHeader* user_header,
                                        const ParamDefineTable* param_define,
                                        sead::BufferedSafeString* dump_str)
{
    // ------------------------------------- ResUserHeader -----------------------------------------
    dumpLine_(dump_str, "<< ResUserHeader[%d] (addr:0x%x, name=%s) >>\n", user_index, reinterpret_cast<u64>(user_header),
              user_name.cstr());
    dumpLine_(dump_str, "    isSetup: %u\n", user_header->isSetup);
    dumpLine_(dump_str, "    numLocalProperty: %u\n", user_header->numLocalProperty);
    dumpLine_(dump_str, "    numCallTable: %u\n", user_header->numCallTable);
    dumpLine_(dump_str, "    numAsset: %u\n", user_header->numAsset);
    dumpLine_(dump_str, "    numRandomContainer2: %u\n", user_header->numRandomContainer2);
    dumpLine_(dump_str, "    numResActionSlot: %u\n", user_header->numResActionSlot);
    dumpLine_(dump_str, "    numResAction: %u\n", user_header->numResAction);
    dumpLine_(dump_str, "    numResActionTrigger: %u\n", user_header->numResActionTrigger);
    dumpLine_(dump_str, "    numResProperty: %u\n", user_header->numResProperty);
    dumpLine_(dump_str, "    numResPropertyTrigger: %u\n", user_header->numResPropertyTrigger);
    dumpLine_(dump_str, "    numResAlwaysTrigger: %u\n", user_header->numResAlwaysTrigger);
    dumpLine_(dump_str, "    triggerTablePos: %u\n", user_header->triggerTablePos);
    dumpLine_(dump_str, "\n");


    // ------------------------------- LocalPropertyNameRefTable -----------------------------------
    
    s32* name_ref_table {reinterpret_cast<s32*>(user_header + 1)};

    dumpLine_(dump_str, "    << LocalPropertyNameRefTable (addr:0x%x, num=%d) >>\n", reinterpret_cast<u64>(name_ref_table), user_header->numLocalProperty);
    
    for (u32 i {0}; i < user_header->numLocalProperty; ++i)
        dumpLine_(dump_str, "        [%d]: namePos=%d\n", i, name_ref_table[i]);

    dumpLine_(dump_str, "\n");

    // --------------------------------------- UserParamTable --------------------------------------
    
    ResParam* user_param_table {reinterpret_cast<ResParam*>(name_ref_table + user_header->numLocalProperty)};
    u32 num_user_param {param_define->getNumUserParam()};
    
    dumpLine_(dump_str, "    << UserParamTable (addr:0x%x, num=%d) >>\n", reinterpret_cast<u64>(user_param_table), num_user_param);
    for (u32 i {0}; i < num_user_param; ++i) {
        dumpLine_(dump_str, "        [%d] rawValue: %u (type: %d, value: %d)\n", i,
                    user_param_table[i].rawValue, user_param_table[i].getRefType(), user_param_table[i].getValue());
    }
    dumpLine_(dump_str, "\n");

    // ------------------------------------- SortedAssetIdTable ------------------------------------
    
    u16* sorted_asset_id_table {reinterpret_cast<u16*>(user_param_table + num_user_param)};
    dumpLine_(dump_str, "    << SortedAssetIdTable (addr:0x%x, num=%d) >>\n", reinterpret_cast<u64>(sorted_asset_id_table), user_header->numCallTable);
    
    for (u32 i {0}; i < user_header->numCallTable; ++i)
        dumpLine_(dump_str, "        [%d]: %hu\n", i, sorted_asset_id_table[i]);

    dumpLine_(dump_str, "\n");

    // --------------------------------------- AssetCallTable --------------------------------------
    
    ResAssetCallTable* asset_call_table {reinterpret_cast<ResAssetCallTable*>(sorted_asset_id_table + user_header->numCallTable)};
    if (user_header->numCallTable & 1)
        asset_call_table  = reinterpret_cast<ResAssetCallTable*>(sorted_asset_id_table + user_header->numCallTable + 1);

    dumpLine_(dump_str, "    << AssetCallTable (addr:0x%x, num=%d) >>\n", reinterpret_cast<u64>(asset_call_table), user_header->numCallTable);
    for (u32 i {0}; i < user_header->numCallTable; ++i) {
        dumpLine_(dump_str, "        [%d].keyNamePos: %u\n", i, asset_call_table[i].keyNamePos);
        dumpLine_(dump_str, "        [%d].assetId: %hd\n", i, asset_call_table[i].assetId);
        dumpLine_(dump_str, "        [%d].flag: %hu\n", i, asset_call_table[i].flag);
        dumpLine_(dump_str, "        [%d].parentIndex: %d\n", i, asset_call_table[i].parentIndex);
        dumpLine_(dump_str, "        [%d].paramStartPos: %u\n", i, asset_call_table[i].paramStartPos);
        dumpLine_(dump_str, "        [%d].conditionPos: %u\n", i, asset_call_table[i].conditionPos);
    }
    dumpLine_(dump_str, "\n");

    // --------------------------------------- ContainerTable --------------------------------------
    
    ResContainerParam* container {reinterpret_cast<ResContainerParam*>(asset_call_table + user_header->numCallTable)};
    u32 num_container {user_header->numCallTable - user_header->numAsset};

    dumpLine_(dump_str, "    << ContainerTable (addr:0x%x, num=%d) >>\n", reinterpret_cast<u64>(container), num_container);
    for (u32 i {0}; i < num_container; ++i) {
        switch (container->type) {
        case ContainerType::Switch: {
            auto* switch_container {static_cast<ResSwitchContainerParam*>(container)};
            volatile ContainerType* type {&switch_container->type};

            dumpLine_(dump_str, "        [%d].type: %d\n",                  i,  *type);
            dumpLine_(dump_str, "        [%d].childrenStartIndex: %d\n",    i,  switch_container->childrenStartIndex);
            dumpLine_(dump_str, "        [%d].childrenEndIndex: %d\n",      i,  switch_container->childrenEndIndex);
            dumpLine_(dump_str, "        [%d].watchPropertyNamePos: %u\n",  i,  switch_container->watchPropertyNamePos);
            dumpLine_(dump_str, "        [%d].watchPropertyId: %d\n",       i,  switch_container->watchPropertyId);
            dumpLine_(dump_str, "        [%d].localPropertyNameIdx: %hd\n", i,  switch_container->localPropertyNameIdx);
            dumpLine_(dump_str, "        [%d].isGlobal: %d\n",              i,  switch_container->isGlobal);
            
            container = static_cast<ResContainerParam*>(switch_container + 1);
            break;
        }
        default:
            dumpLine_(dump_str, "        [%d].type: %d\n",                  i,  container->type);
            dumpLine_(dump_str, "        [%d].childrenStartIndex: %d\n",    i,  container->childrenStartIndex);
            dumpLine_(dump_str, "        [%d].childrenEndIndex: %d\n",      i,  container->childrenEndIndex);
            
            container += 1;
            break;
        }
    }
    dumpLine_(dump_str, "\n");

    // ------------------------------------- ResActionSlotTable ------------------------------------
    
    ResActionSlot* action_slot_table {calcOffset<ResActionSlot>(reinterpret_cast<u64>(user_header) + user_header->triggerTablePos)};

    dumpLine_(dump_str, "    << ResActionSlotTable (addr:0x%x, num=%d) >>\n", reinterpret_cast<u64>(action_slot_table), user_header->numResActionSlot);
    for (u32 i{0}; i < user_header->numResActionSlot; ++i) {
        dumpLine_(dump_str,
                    "        [%d] namePos: %u, actionStartIdx: %hd, actionEndIdx: %hd\n", i,
                    action_slot_table[i].namePos, action_slot_table[i].actionStartIdx, action_slot_table[i].actionEndIdx);
    }
    dumpLine_(dump_str, "\n");

    // --------------------------------------- ResActionTable --------------------------------------
    
    ResAction* action_table {reinterpret_cast<ResAction*>(action_slot_table + user_header->numResActionSlot)};

    dumpLine_(dump_str, "    << ResActionTable (addr:0x%x, num=%d) >>\n", reinterpret_cast<u64>(action_table), user_header->numResAction);
    for (u32 i {0}; i < user_header->numResAction; ++i) {
        dumpLine_(dump_str,
                    "        [%d] namePos: %u, triggerStartIdx: %d, triggerEndIdx: %d\n", i,
                    action_table[i].namePos, action_table[i].triggerStartIdx, action_table[i].triggerEndIdx);
    }
    dumpLine_(dump_str, "\n");

    // ----------------------------------- ResActionTriggerTable ----------------------------------
    
    ResActionTrigger* action_trigger_table {reinterpret_cast<ResActionTrigger*>(action_table + user_header->numResAction)};

    dumpLine_(dump_str, "    << ResActionTriggerTable (addr:0x%x, num=%d) >>\n", reinterpret_cast<u64>(action_trigger_table), user_header->numResActionTrigger);
    for (u32 i {0}; i < user_header->numResActionTrigger; ++i) {
        dumpLine_(dump_str, "        [%d].guId: %d\n", i, action_trigger_table[i].guId);
        dumpLine_(dump_str, "        [%d].assetCtbPos: %u\n", i, action_trigger_table[i].assetCtbPos);
        dumpLine_(dump_str, "        [%d].startFrame: %d\n", i, action_trigger_table[i].startFrame);
        dumpLine_(dump_str, "        [%d].endFrame: %d\n", i, action_trigger_table[i].endFrame);
        dumpLine_(dump_str, "        [%d].flag: %hu\n", i, action_trigger_table[i].flag);
        dumpLine_(dump_str, "        [%d].overwriteHash: %hd\n", i, action_trigger_table[i].overwriteHash);
        dumpLine_(dump_str, "        [%d].overwriteParamPos: %u\n", i, action_trigger_table[i].overwriteParamPos);
    }
    dumpLine_(dump_str, "\n");

    // -------------------------------------- ResPropertyTable -------------------------------------
    
    ResProperty* property_table {reinterpret_cast<ResProperty*>(action_trigger_table + user_header->numResActionTrigger)};

    dumpLine_(dump_str, "    << ResPropertyTable (addr:0x%x, num=%d) >>\n", reinterpret_cast<u64>(property_table), user_header->numResProperty);
    for (u32 i {0}; i < user_header->numResProperty; ++i) {
        dumpLine_(dump_str,
                    "        [%d] watchPropertyNamePos: %u, isGlobal: %d, triggerStartIdx: %d, triggerEndIdx: %d\n", i,
                    property_table[i].watchPropertyNamePos, property_table[i].isGlobal,
                    property_table[i].triggerStartIdx, property_table[i].triggerEndIdx);
    }
    dumpLine_(dump_str, "\n");

    // ---------------------------------- ResPropertyTriggerTable ---------------------------------
    
    ResPropertyTrigger* property_trigger_table {reinterpret_cast<ResPropertyTrigger*>(property_table + user_header->numResProperty)};
    
    dumpLine_(dump_str, "    << ResPropertyTriggerTable (addr:0x%x, num=%d) >>\n", reinterpret_cast<u64>(property_trigger_table), user_header->numResPropertyTrigger);
    for (u32 i {0}; i < user_header->numResPropertyTrigger; ++i) {
        dumpLine_(dump_str, "        [%d].guId: %d\n", i, property_trigger_table[i].guId);
        dumpLine_(dump_str, "        [%d].assetCtbPos: %u\n", i, property_trigger_table[i].assetCtbPos);
        dumpLine_(dump_str, "        [%d].condition: %u\n", i, property_trigger_table[i].condition);
        dumpLine_(dump_str, "        [%d].flag: %hu\n", i, property_trigger_table[i].flag);
        dumpLine_(dump_str, "        [%d].overwriteHash: %hd\n", i, property_trigger_table[i].overwriteHash);
        dumpLine_(dump_str, "        [%d].overwriteParamPos: %u\n", i, property_trigger_table[i].overwriteParamPos);
    }
    dumpLine_(dump_str, "\n");

    // ----------------------------------- ResAlwaysTriggerTable ----------------------------------
    
    ResAlwaysTrigger* always_trigger_table {reinterpret_cast<ResAlwaysTrigger*>(property_trigger_table + user_header->numResPropertyTrigger)};

    dumpLine_(dump_str, "    << ResAlwaysTriggerTable (addr:0x%x, num=%d) >>\n", reinterpret_cast<u64>(always_trigger_table), user_header->numResAlwaysTrigger);
    for (u32 i {0}; i < user_header->numResAlwaysTrigger; ++i) {
        dumpLine_(dump_str, "        [%d].guId: %d\n", i, always_trigger_table[i].guId);
        dumpLine_(dump_str, "        [%d].assetCtbPos: %u\n", i, always_trigger_table[i].assetCtbPos);
        dumpLine_(dump_str, "        [%d].flag: %hu\n", i, always_trigger_table[i].flag);
        dumpLine_(dump_str, "        [%d].overwriteHash: %hd\n", i, always_trigger_table[i].overwriteHash);
        dumpLine_(dump_str, "        [%d].overwriteParamPos: %u\n", i, always_trigger_table[i].overwriteParamPos);
    }
    dumpLine_(dump_str, "\n");
}

void ResourceParamCreator::dumpCommonResourceRear_(CommonResourceParam* common_res_param,
                                                   const BinAccessor* bin_accessor, u32 data_size,
                                                   sead::Heap* heap, bool p2,
                                                   sead::BufferedSafeString* dump_str)
{
    // --------------------------------------- ConditionTable --------------------------------------
    dumpLine_(dump_str, "<< ConditionTable (addr:0x%x, size:%d) >>\n",
              common_res_param->conditionTablePos,
              common_res_param->nameTablePos - common_res_param->conditionTablePos);

    u32 pos {common_res_param->conditionTablePos};
    for (s32 i {0}, condition_size {0}; pos < common_res_param->nameTablePos; ++i, pos += condition_size) {
        auto* res_condition {reinterpret_cast<ResCondition*>((pos >= sMinAddressLow) ? 
                                                             (pos | sMinAddressHigh) :
                                                             (pos | sMinAddressHigh) + 0x100000000)};


        switch (res_condition->parentContainerType) {
        case ContainerType::Switch: {
            SwitchCondition* condition {static_cast<SwitchCondition*>(res_condition)};
            dumpLine_(dump_str, "  [%d].parentContainerType: %d\n", i, condition->parentContainerType);
            dumpLine_(dump_str, "  [%d].propertyType: %d\n", i, condition->propertyType);
            dumpLine_(dump_str, "  [%d].compareType: %d\n", i, condition->compareType);
            dumpLine_(dump_str, "  [%d].value: %d\n", i, condition->value);
            dumpLine_(dump_str, "  [%d].localPropertyEnumNameIdx: %d\n", i, condition->localPropertyEnumNameIdx);
            dumpLine_(dump_str, "  [%d].isSolved: %d\n", i, condition->isSolved);
            dumpLine_(dump_str, "  [%d].isGlobal: %d\n", i, condition->isGlobal);
            
            condition_size = sizeof(SwitchCondition);
            break;
        }
        case ContainerType::Random:
        case ContainerType::Random2: {
            RandomCondition* condition {static_cast<RandomCondition*>(res_condition)};
            dumpLine_(dump_str, "  [%d].parentContainerType: %d\n", i, condition->parentContainerType);
            dumpLine_(dump_str, "  [%d].weight: %.4f\n", i, condition->weight);
            
            condition_size = sizeof(RandomCondition);
            break;
        }
        default:
            condition_size = 0;
            break;
        }
    }
    dumpLine_(dump_str, "\n");

    // ----------------------------------------- NameTable -----------------------------------------
    u32 name_table_pos {bin_accessor->resourceHeader ? bin_accessor->resourceHeader->nameTablePos : bin_accessor->editorHeader->nameTablePos};
    u32 name_table_size = data_size - name_table_pos;

    dumpLine_(dump_str, "<< NameTable (addr:0x%x, size:%d) >>\n",
              common_res_param->nameTablePos, name_table_size);
    if (name_table_size != 0) {
        char* dest = new (heap) char[name_table_size];
        char* src = calcOffset<char>(common_res_param->nameTablePos);
        memcpy(dest, src, name_table_size);

        for (s32 i {0}; i < name_table_size - 1; ++i) {
            if (dest[i] == '\0')
                dest[i] = ' ';
        }

        dumpLine_(dump_str, "  {%s}\n", dest);
        delete[] dest;
    }
    dumpLine_(dump_str, "\n");
}

void ResourceParamCreator::dumpLine_(sead::BufferedSafeString* dump_str, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    sead::FixedSafeString<256> msg;
    msg.formatV(fmt, args);
    va_end(args);
    if (dump_str != nullptr)
        dump_str->appendWithFormat("%s", msg.cstr());
}
}  // namespace xlink2
