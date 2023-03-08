#include <cstddef>

#include "xlink2/xlink2Condition.h"
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
    rom_res_param->assetParamTable = nullptr;
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

// WIP
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
        ResAssetParam* res_asset_table{(ResAssetParam*)(bin_accessor->mBinEnd | sMinAddressHigh)};
        if (bin_accessor->mBinEnd < sMinAddressLow) {
            res_asset_table += 0x8000000;
        }
        common_res_param->assetParamTable = res_asset_table;
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
        common_res_param->randomCallTable = (ResRandomCallTable*)ptr_follower;
    ptr_follower += common_res_param->numRandomTable;

    if (common_res_param->numCurveTable != 0)
        common_res_param->curveCallTable = (ResCurveCallTable*)ptr_follower;
    ptr_follower += common_res_param->numCurveTable;

    if (common_res_param->numCurvePointTable != 0)
        common_res_param->curvePointTable = (CurvePoint*)ptr_follower;

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

// WIP
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
                v2 = (ResUserHeader*)&v2[0x5555555].numRandomContainer2;
            }
            dumpUserBin_(i, str_v, v2, param_define, buffered_str);
        }
    }
    dumpCommonResourceRear_(rom_res, bin_accessor, res_header->dataSize, heap, false, buffered_str);
}

// WIP
void dumpEditorResource_(EditorResourceParam* editor_resource, const BinAccessor* bin_accessor,
                         const ParamDefineTable* param_define, sead::Heap* heap) {
    sead::BufferedSafeString* buffered_str{nullptr};

    dumpLine_(buffered_str, "[XLink2] EditorBuffer dump\n");

    EditorHeader* editor_header{editor_resource->pEditorHeader};
    sead::SafeString* editor_name{editor_resource->editorName};

    dumpLine_(buffered_str, "<< EditorHeader[%s] (addr:0x%x, size:%@) >>\n",
              editor_resource->editorName2, editor_header, 0x44);
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
    dumpUserBin_(0, *editor_name, editor_resource->pResUserHeader, param_define, buffered_str);
    dumpCommonResourceRear_(editor_resource, bin_accessor, editor_resource->_0, heap, false,
                            buffered_str);
}

// WIP
void dumpCommonResourceFront_(CommonResourceParam* common_res_param,
                              const BinAccessor* bin_accessor, bool p1,
                              sead::BufferedSafeString* buffered_str) {
    u32 all_asset_param_num;
    u32 not_default_param_num;
    u32 overwrite_num;
    u32 all_trigger_overwrite_param_num;
    u32 v3;
    u32 asset_param_raw_value;

    // ----------------------------- ResAssetParamTable ---------------------------------
    dumpLine_(buffered_str, "<< ResAssetParamTable (addr:0x%x, size:print later) >>\n",
              common_res_param->assetParamTable);

    ResAssetParam* pv1{common_res_param->assetParamTable};
    ResAssetParam* pv2{pv1};
    u32* next_raw_value;
    u32* raw_value_ptr;

    if (common_res_param->numResAssetParam == 0) {
        all_asset_param_num = 0;
        not_default_param_num = 0;
    } else if (p1) {
        not_default_param_num = 0;
        all_asset_param_num = 0;
        for (int i{0}; i < common_res_param->numResAssetParam; ++i) {
            next_raw_value = pv2->rawValue;
            dumpLine_(buffered_str, "  [%d] mask: %lu\n", i, pv2->mask);
            if (bin_accessor->mUserParamNum != 0) {
                raw_value_ptr = pv2->rawValue;
                for (int j{0}; j < bin_accessor->mUserParamNum; ++j) {
                    if ((pv2->mask & 1L << j & 0x3f) == 0) {
                        dumpLine_(buffered_str,
                                  "  [%d] param of bit[%d]: not exist(default value)\n", i, j);
                    } else {
                        asset_param_raw_value = *raw_value_ptr;
                        dumpLine_(
                            buffered_str,
                            "  [%d] param of bit[%d]: rawValue: %u(referenceType: %d, value: %d)\n",
                            i, j, asset_param_raw_value, asset_param_raw_value >> 0x18,
                            asset_param_raw_value & 0xffffff);
                        not_default_param_num += 1;
                        next_raw_value += 4;
                        raw_value_ptr += 1;
                    }
                    v3 = j;
                }
                all_asset_param_num += v3;
            }
            pv2->rawValue = raw_value_ptr;
        }
    } else {
        not_default_param_num = 0;
        all_asset_param_num = 0;
        for (int i{0}; i < common_res_param->numResAssetParam; ++i) {
            next_raw_value = pv2->rawValue;
            if (bin_accessor->mUserParamNum != 0) {
                for (int j{0}; j < bin_accessor->mUserParamNum; ++j) {
                    if (pv2->mask & 1L << j & 0x3f != 0) {
                        not_default_param_num += 1;
                        next_raw_value += 1;
                    }
                    v3 = j;
                }
                all_asset_param_num += v3;
            }
        }
    }

    if (!p1)
        dumpLine_(buffered_str, "  ...no content print.\n");
    dumpLine_(buffered_str,
              "<< ResAssetParamTable finished(size:%d, allParamNum=%d, notDefaultParamNum=%d) >>\n",
              (u64)pv2 - (u64)pv1, all_asset_param_num, not_default_param_num);

    // ----------------------------- ResTriggerOverwriteParamTable ---------------------------------
    u32 pos;

    if (!bin_accessor->mResourceHeader)
        pos = bin_accessor->mEditorHeader->triggerOverwriteParamTablePos;
    else
        pos = bin_accessor->mResourceHeader->triggerOverwriteParamTablePos;

    dumpLine_(buffered_str, "<< ResTriggerOverwriteParamTable (addr:0x%x, size:print later) >>\n",
              pos);

    u32 trigger_pos{common_res_param->triggerOverwriteParamTablePos};
    u32 trigger_end{0};
    if (common_res_param->numResTriggerOverwriteParam == 0) {
        all_trigger_overwrite_param_num = 0;
        overwrite_num = 0;
    } else if (p1) {
        for (int i{0}; i < common_res_param->numResTriggerOverwriteParam; ++i) {
            u64* v5{(u64*)(sMinAddressHigh | trigger_pos)};
            if (trigger_pos < sMinAddressHigh)
                v5 = (u64*)(sMinAddressHigh | trigger_pos + 0x40000000);
            dumpLine_(buffered_str, "  [%d] mask: %lu\n", i, *v5);
            u64 v6{(u64)v5 + 4};
            if (bin_accessor->mAssetParamNum != 0) {
                u64* v7{v5 + 1};
                for (int j{0}; j < bin_accessor->mAssetParamNum; ++j) {
                    if ((*v5 & 1 << j & 0x1f) == 0)
                        dumpLine_(buffered_str,
                                  "  [%d] param of bit[%d]: not exist(not overwritten)\n", i, j);
                    else {
                        u64 v8{*v7};
                        dumpLine_(
                            buffered_str,
                            "  [%d] param of bit[%d]: rawValue: %u(referenceType: %d, value: %d)\n",
                            i, j, v8, v8 >> 0x18, v8 & 0xffffff);
                        ++overwrite_num;
                        v6 += 4;
                        ++v7;
                    }
                }
                all_trigger_overwrite_param_num = bin_accessor->mAssetParamNum;
            }
        }
    } else {
        u64 current_pos{trigger_pos};
        for (int i{0}; i < common_res_param->numResTriggerOverwriteParam; ++i) {
            u64 v5{current_pos + 4};
            if (bin_accessor->mAssetParamNum != 0) {
                u64* v6{(u64*)(sMinAddressHigh | current_pos)};
                if (current_pos < sMinAddressLow)
                    v6 = (u64*)(sMinAddressHigh | current_pos + 0x40000000);

                u64 v7{v5};
                for (int j{0}; j < bin_accessor->mAssetParamNum; ++j) {
                    if ((*v6 & 1 << j & 0x1f) != 0) {
                        ++overwrite_num;
                        v7 = v5 + 4;
                    }
                    v5 = v7;
                }
                all_trigger_overwrite_param_num = bin_accessor->mAssetParamNum;
                trigger_end = v7;
            }
        }
    }

    if (!p1) {
        dumpLine_(buffered_str, "  ...no content print.\n");
    }

    dumpLine_(
        buffered_str,
        "<< ResTriggerOverwriteParamTable finished(size:%d, allParamNum=%d, overwriteNum=%d) >>\n",
        trigger_end - trigger_pos, all_trigger_overwrite_param_num, overwrite_num);
    dumpLine_(buffered_str, "\n");

    // --------------------------------- LocalPropertyNameRefTable ---------------------------------
    dumpLine_(buffered_str, "<< LocalPropertyNameRefTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->localPropertyNameRefTable, 8,
              common_res_param->numLocalPropertyNameRefTable,
              common_res_param->numLocalPropertyNameRefTable << 3);

    if (p1 && common_res_param->numLocalPropertyNameRefTable != 0)
        for (int i{0}; i < common_res_param->numLocalPropertyNameRefTable; ++i)
            dumpLine_(buffered_str, "  [%d] namePos=%d\n", i,
                      (u64)common_res_param->localPropertyNameRefTable + static_cast<u64>(i * 4));
    else
        dumpLine_(buffered_str, "  ...no content print.\n");
    dumpLine_(buffered_str, "\n");

    // ----------------------------- LocalPropertyEnumNameRefTable ---------------------------------
    dumpLine_(buffered_str, "<< LocalPropertyEnumNameRefTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->localPropertyEnumNameRefTable, 8,
              common_res_param->numLocalPropertyEnumNameRefTable,
              common_res_param->numLocalPropertyEnumNameRefTable << 3);

    if (p1 && common_res_param->numLocalPropertyEnumNameRefTable != 0)
        for (int i{0}; i < common_res_param->numLocalPropertyEnumNameRefTable; ++i)
            dumpLine_(buffered_str, "  [%d] enumNamePos=%d\n", i,
                      (u64)common_res_param->localPropertyEnumNameRefTable +
                          static_cast<u64>(i * 4));
    else
        dumpLine_(buffered_str, "  ...no content print.\n");
    dumpLine_(buffered_str, "\n");

    // ----------------------------------- DirectValueTable ----------------------------------------
    dumpLine_(buffered_str, "<< DirectValueTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->directValueTable, 4, common_res_param->numDirectValueTable,
              common_res_param->numDirectValueTable << 2);
    if (p1 && common_res_param->numDirectValueTable != 0)
        for (int i{0}; i < common_res_param->numDirectValueTable; ++i)
            dumpLine_(buffered_str, "  [%d] directvalue=%d\n", i,
                      (u64)common_res_param->directValueTable + static_cast<u64>(i * 4));
    else
        dumpLine_(buffered_str, "  ...no content print.\n");
    dumpLine_(buffered_str, "\n");

    // ------------------------------------ RandomCallTable ----------------------------------------
    dumpLine_(buffered_str, "<< RandomCallTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->randomCallTable, 8, common_res_param->numRandomTable,
              common_res_param->numRandomTable << 3);
    if (p1 && common_res_param->numRandomTable != 0)
        for (int i{0}; i < common_res_param->numRandomTable; ++i)
            dumpLine_(buffered_str, "  [%d] minValue=%.4f, maxValue=%.4f\n",
                      common_res_param->randomCallTable[i].minValue,
                      common_res_param->randomCallTable[i].maxValue, i);
    else
        dumpLine_(buffered_str, "  ...no content print.\n");
    dumpLine_(buffered_str, "\n");

    // ------------------------------------- CurveCallTable ----------------------------------------
    dumpLine_(buffered_str, "<< CurveCallTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->curveCallTable, sizeof(ResCurveCallTable),
              common_res_param->numCurveTable,
              common_res_param->numCurveTable * sizeof(ResCurveCallTable));
    if (p1 && common_res_param->numCurveTable != 0) {
        for (int i{0}; i < common_res_param->numCurveTable; ++i) {
            dumpLine_(buffered_str, "  [%d].curvePointStartPos: %hu\n", i,
                      common_res_param->curveCallTable[i].curvePointStartPos);
            dumpLine_(buffered_str, "  [%d].numPoint: %hu\n", i,
                      common_res_param->curveCallTable[i].numPoint);
            dumpLine_(buffered_str, "  [%d].curveType: %hu\n", i,
                      common_res_param->curveCallTable[i].curveType);
            dumpLine_(buffered_str, "  [%d].isPropGlobal: %hu\n", i,
                      common_res_param->curveCallTable[i].isPropGlobal);
            dumpLine_(buffered_str, "  [%d].propName: %u\n", i,
                      common_res_param->curveCallTable[i].propName);
            dumpLine_(buffered_str, "  [%d].propIdx: %d\n", i,
                      common_res_param->curveCallTable[i].propIdx);
            dumpLine_(buffered_str, "  [%d].localPropertyNameIdx: %hd\n", i,
                      common_res_param->curveCallTable[i].localPropertyNameIdx);
        }
    } else
        dumpLine_(buffered_str, "  ...no content print.\n");
    dumpLine_(buffered_str, "\n");

    // ------------------------------------ CurvePointTable ----------------------------------------
    dumpLine_(buffered_str, "<< CurvePointTable (addr:0x%x, size:%d*%u=%u) >>\n",
              common_res_param->curvePointTable, sizeof(CurvePoint),
              common_res_param->numCurvePointTable, common_res_param->numCurvePointTable << 3);
    if (p1 && common_res_param->numCurvePointTable != 0)
        for (int i{0}; i < common_res_param->numCurvePointTable; ++i)
            dumpLine_(buffered_str, "  [%d] x=%.4f, y=%.4f\n",
                      common_res_param->curvePointTable[i].x,
                      common_res_param->curvePointTable[i].y, i);
    else
        dumpLine_(buffered_str, "  ...no content print.\n");
    dumpLine_(buffered_str, "\n");

    dumpLine_(buffered_str, "<< ExRegion (addr:0x%x, size:unknown) >>\n",
              common_res_param->exRegionPos);
    sead::SafeString s;
    if (p1)
        s = "  ...not dump content.\n";
    else
        s = "  ...no content print.\n";
    dumpLine_(buffered_str, s.cstr());
    dumpLine_(buffered_str, "\n");
};

// WIP
void dumpUserBin_(u32 p1, const sead::SafeString& user_name, ResUserHeader* user_header,
                  const ParamDefineTable* param_define, sead::BufferedSafeString* buffered_str) {
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
    u32 user_param_num{param_define->getUserParamNum()};
    u64 pos2{pos + num_property * sizeof(u32)};
    dumpLine_(buffered_str, "    << UserParamTable (addr:0x%x, num=%d) >>\n", pos2, user_param_num);

    if (user_param_num != 0) {
        for (int i{0}; i < user_param_num; ++i) {
            // TODO: This looks weird. Take a look later
            u32* raw_value{&user_header->userParamTablePos};
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
            } else {
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
void dumpCommonResourceRear_(CommonResourceParam* common_res_param, const BinAccessor* bin_accessor,
                             u32 p1, sead::Heap* heap, bool p2,
                             sead::BufferedSafeString* buffered_str) {
    // --------------------------------------- ConditionTable --------------------------------------
    dumpLine_(buffered_str, "<< ConditionTable (addr:0x%x, size:%d) >>\n",
              common_res_param->conditionTablePos,
              common_res_param->nameTablePos - common_res_param->conditionTablePos, p2);

    u32 pos1{common_res_param->conditionTablePos};
    u32 condition_size;
    ResCondition* condition;
    for (int i{0}; pos1 < common_res_param->nameTablePos; ++i) {
        condition = (ResCondition*)(sMinAddressHigh | pos1);
        if (pos1 < sMinAddressLow)
            condition += 0x40000000;

        if (condition->parentContainerType < ContainerType::Random2) {
            RandomCondition* condition = condition;
            dumpLine_(buffered_str, "  [%d].parentContainerType: %d\n", i,
                      condition->parentContainerType);
            dumpLine_(buffered_str, "  [%d].weight: %.4f\n", i, condition->weight);
            condition_size = sizeof(RandomCondition);
        } else {
            condition_size = 0;
            if (condition->parentContainerType == ContainerType::Switch) {
                dumpLine_(buffered_str, "  [%d].parentContainerType: %d\n", i,
                          condition->parentContainerType);
                dumpLine_(buffered_str, "  [%d].propertyType: %d\n", i, condition->propertyType);
                dumpLine_(buffered_str, "  [%d].compareType: %d\n", i, condition->compareType);
                dumpLine_(buffered_str, "  [%d].value: %d\n", i, condition->value);
                dumpLine_(buffered_str, "  [%d].localPropertyEnumNameIdx: %d\n", i,
                          condition->localPropertyEnumNameIdx);
                dumpLine_(buffered_str, "  [%d].isSolved: %d\n", i, condition->isSolved);
                dumpLine_(buffered_str, "  [%d].isGlobal: %d\n", i, condition->isGlobal);
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
            u32 ivar3;
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

            delete[] dest;
            return;
        }
    }
};
}  // namespace xlink2::ResourceParamCreator