#include <codec/seadHashCRC32.h>

#include "xlink2/xlink2ResourceParamCreator.h"
#include "xlink2/xlink2ActionTriggerCtrl.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
ResourceParamCreator::BinAccessor::BinAccessor(ResourceHeader* res_header,
                                               const ParamDefineTable* param_define)
{
    pResourceHeader = res_header;
    binStart = reinterpret_cast<u64>(pResourceHeader);

    u8* param_define_start = reinterpret_cast<u8*>(pResourceHeader)
                            + sizeof(ResourceHeader)                    // header
                            + pResourceHeader->numUser * sizeof(u32)    // user hashes
                            + pResourceHeader->numUser * sizeof(u32);   // user offsets

    assetsStart = static_cast<u32>(reinterpret_cast<uintptr_t>(param_define_start)) + param_define->getSize();
    numAssetParam = param_define->getNumAssetParam();
    numTriggerParam = param_define->getNumTriggerParam();
}

ResourceParamCreator::BinAccessor::BinAccessor(EditorHeader* editor_header,
                                               const ParamDefineTable* param_define)
{
    pEditorHeader = editor_header;
    binStart = reinterpret_cast<uintptr_t>(editor_header);
    assetsStart = binStart + sizeof(EditorHeader);
    numAssetParam = param_define->getNumAssetParam();
    numTriggerParam = param_define->getNumTriggerParam();
}

void ResourceParamCreator::createParamAndSolveResource(RomResourceParam* rom_res_param, void* bin,
                                                       ParamDefineTable const* param_define,
                                                       System* system)
{
    *rom_res_param = {};
    rom_res_param->_0 = reinterpret_cast<u64>(bin);
    
    ResourceHeader* header {reinterpret_cast<ResourceHeader*>(bin)};
    u32* name_hash_table {reinterpret_cast<u32*>(header + 1)};
    
    if (header->numUser != 0) {
        rom_res_param->nameHashTable = name_hash_table;
        if (header->numUser != 0)
            rom_res_param->offsetTable = rom_res_param->nameHashTable + header->numUser;
    }
    rom_res_param->numUser = header->numUser;


    BinAccessor bin_accessor {header, param_define};

    createCommonResourceParam_(rom_res_param, &bin_accessor);

    if (system->debugOperationParamOR().getPrintFlag().isOnBit(0))
        dumpRomResource_(header, rom_res_param, &bin_accessor, param_define, system->getPrimaryHeap(), false, nullptr);

    solveCommonResource_(rom_res_param, &bin_accessor);

    for (u32 i {0}; i < rom_res_param->numUser; ++i) {
        u32 user_bin = rom_res_param->offsetTable[i] + static_cast<u32>(reinterpret_cast<u64>(bin));
        rom_res_param->offsetTable[i] = user_bin;
        
        auto* user_header {calcOffset<ResUserHeader>(user_bin)};
        if (user_header->isSetup == 0)
            solveUserBin_(user_header, rom_res_param, param_define);
    }

    if (system->isGlobalPropFixed())
        solveAboutGlobalProperty(rom_res_param, param_define, system);

    rom_res_param->isInitialized = true;
}

// WIP
void ResourceParamCreator::createCommonResourceParam_(CommonResourceParam* common_res_param,
                                                      BinAccessor* bin_accessor)
{
    common_res_param->numResParam = bin_accessor->getNumResParam();
    common_res_param->numResAssetParam = bin_accessor->getNumResAssetParam();
    common_res_param->numResTriggerOverwriteParam = bin_accessor->getNumResTriggerOverwriteParam();
    common_res_param->numLocalPropertyNameRefTable = bin_accessor->getNumLocalPropertyNameRefTable();
    common_res_param->numLocalPropertyEnumNameRefTable = bin_accessor->getNumLocalPropertyEnumNameRefTable();
    common_res_param->numDirectValueTable = bin_accessor->getNumDirectValueTable();
    common_res_param->numRandomTable = bin_accessor->getNumRandomTable();
    common_res_param->numCurveTable = bin_accessor->getNumCurveTable();
    common_res_param->numCurvePointTable = bin_accessor->getNumCurvePointTable();

    ResAssetParam* asset_param_table {calcOffset<ResAssetParam>(bin_accessor->assetsStart)};
    if (common_res_param->numResAssetParam > 0)
        common_res_param->assetParamTable = asset_param_table;

    u32 trigger_overwrite_param_table_pos = bin_accessor->getTriggerOverwriteParamTablePos();
    if (common_res_param->numResTriggerOverwriteParam > 0) {
        common_res_param->triggerOverwriteParamTablePos = trigger_overwrite_param_table_pos + bin_accessor->binStart;
    }

    u32 local_property_name_ref_pos {bin_accessor->getLocalPropertyNameRefTablePos()};
    auto* ptr = calcOffset<u8>(bin_accessor->binStart + local_property_name_ref_pos);
    
    if (common_res_param->numLocalPropertyNameRefTable > 0)
        common_res_param->localPropertyNameRefTable = reinterpret_cast<u32*>(ptr);
    ptr += common_res_param->numLocalPropertyNameRefTable * sizeof(u32);

    if (common_res_param->numLocalPropertyEnumNameRefTable > 0)
        common_res_param->localPropertyEnumNameRefTable = reinterpret_cast<u32*>(ptr);
    ptr += common_res_param->numLocalPropertyEnumNameRefTable * sizeof(u32);

    if (common_res_param->numDirectValueTable > 0)
        common_res_param->directValueTable = reinterpret_cast<s32*>(ptr);
    ptr += common_res_param->numDirectValueTable * sizeof(s32);

    if (common_res_param->numRandomTable > 0)
        common_res_param->randomCallTable = reinterpret_cast<ResRandomCallTable*>(ptr);
    ptr += common_res_param->numRandomTable * sizeof(ResRandomCallTable);

    if (common_res_param->numCurveTable > 0)
        common_res_param->curveCallTable = reinterpret_cast<ResCurveCallTable*>(ptr);
    ptr += common_res_param->numCurveTable * sizeof(ResCurveCallTable);

    if (common_res_param->numCurvePointTable > 0)
        common_res_param->curvePointTable = reinterpret_cast<CurvePoint*>(ptr);;

    common_res_param->exRegionPos = bin_accessor->getExRegionPos() + bin_accessor->binStart;
    common_res_param->conditionTablePos = bin_accessor->getConditionTablePos() + bin_accessor->binStart;
    common_res_param->nameTablePos = bin_accessor->getNameTablePos() + bin_accessor->binStart;
}

void ResourceParamCreator::dumpRomResource_(ResourceHeader* res_header, RomResourceParam* rom_res_param,
                                            const BinAccessor* bin_accessor,
                                            const ParamDefineTable* param_define, sead::Heap* heap,
                                            bool p1, sead::BufferedSafeString* buffered_str)
{
    dumpLine_(buffered_str, "[XLink2] ResourceBuffer dump\n");
    dumpLine_(buffered_str, "<< ResourceHeader (addr:0x%x, size:%@) >>\n", res_header, sizeof(ResourceHeader));

    sead::FixedSafeString<5> magic;
    magic.format((char*)res_header->magic);
    dumpLine_(buffered_str, "  magic: %s\n", magic.getBuffer());
    dumpLine_(buffered_str, "  dataSize: %@\n", res_header->dataSize);
    dumpLine_(buffered_str, "  version: %@\n", res_header->version);
    dumpLine_(buffered_str, "  numResParam: %@\n", res_header->numResParam);
    dumpLine_(buffered_str, "  numResAssetParam: %@\n", res_header->numResAssetParam);
    dumpLine_(buffered_str, "  numResTriggerOverwirteParam: %@\n", res_header->numResTriggerOverwriteParam);
    dumpLine_(buffered_str, "  triggerOverwriteParamTablePos: %@\n", res_header->triggerOverwriteParamTablePos);
    dumpLine_(buffered_str, "  localPropertyNameRefTablePos: %@\n", res_header->localPropertyNameRefTablePos);
    dumpLine_(buffered_str, "  numLocalPropertyNameRefTable: %@\n", res_header->numLocalPropertyNameRefTable);
    dumpLine_(buffered_str, "  numLocalPropertyEnumNameRefTable: %@\n", res_header->numLocalPropertyEnumNameRefTable);
    dumpLine_(buffered_str, "  numDirectValueTable: %@\n", res_header->numDirectValueTable);
    dumpLine_(buffered_str, "  numRandomTable: %@\n", res_header->numRandomTable);
    dumpLine_(buffered_str, "  numCurveTable: %@\n", res_header->numCurveTable);
    dumpLine_(buffered_str, "  numCurvePointTable: %@\n", res_header->numCurvePointTable);
    dumpLine_(buffered_str, "  numUser: %@\n", res_header->numUser);
    dumpLine_(buffered_str, "  conditionTablePos: %@\n", res_header->conditionTablePos);
    dumpLine_(buffered_str, "  nameTablePos: %@\n", res_header->nameTablePos);
    dumpLine_(buffered_str, "\n");

    u32 offset_table_size = res_header->numUser * sizeof(u32);
    dumpLine_(buffered_str, "<< OffsetTable (addr:0x%x, size:%@*%@=%@) >>\n", rom_res_param->offsetTable,
              sizeof(u32), res_header->numUser, offset_table_size);
    if (res_header->numUser != 0) {
        for (u32 i{0}; i < res_header->numUser; ++i)
            dumpLine_(buffered_str, "  [%d] binPos=%@, nameHash=%@\n", i, rom_res_param->offsetTable[i],
                      rom_res_param->nameHashTable[i]);
    }
    dumpLine_(buffered_str, "\n");

    dumpLine_(buffered_str, "<< ParamDefineTable (addr:0x%x, size:%@) >>\n", reinterpret_cast<u64>(rom_res_param->offsetTable) + offset_table_size,
              param_define->getSize());
    dumpLine_(buffered_str, "  ...no content print.\n\n");

    dumpCommonResourceFront_(rom_res_param, bin_accessor, p1, buffered_str);
    if (p1 && res_header->numUser != 0) {
        for (u32 i{0}; i < res_header->numUser; ++i) {
            u64 user_offset = rom_res_param->offsetTable[i] + bin_accessor->binStart;
            auto* user_header = reinterpret_cast<ResUserHeader*>((user_offset >= sMinAddressLow) ? 
                                        (user_offset | sMinAddressHigh) :
                                        (user_offset | sMinAddressHigh) + 0x100000000);
            dumpUserBin_(i, "", user_header, param_define,
                         buffered_str);
        }
    }
    dumpCommonResourceRear_(rom_res_param, bin_accessor, res_header->dataSize, heap, false, buffered_str);
}

void ResourceParamCreator::solveCommonResource_(CommonResourceParam * common_res_param, BinAccessor * bin_accessor)
{
    for (u32 i {0}; i < common_res_param->numLocalPropertyNameRefTable; ++i)
        common_res_param->localPropertyNameRefTable[i] += common_res_param->nameTablePos;

    for (u32 i {0}; i < common_res_param->numLocalPropertyEnumNameRefTable; ++i)
        common_res_param->localPropertyEnumNameRefTable[i] += common_res_param->nameTablePos;

    for (u32 i {0}; i < common_res_param->numCurveTable; ++i)
        common_res_param->curveCallTable[i].propName += common_res_param->nameTablePos;

    for (u32 i {common_res_param->conditionTablePos}, condition_size {0}; i < common_res_param->nameTablePos; i += condition_size) {
        auto* res_condition {calcOffset<ResCondition>(i)};

        switch (res_condition->parentContainerType) {
        case ContainerType::Switch: {
            SwitchCondition* condition {static_cast<SwitchCondition*>(res_condition)};

            if (condition->propertyType == PropertyType::Enum)
                condition->value += common_res_param->nameTablePos;
            
            condition_size = sizeof(SwitchCondition);
            break;
        }
        case ContainerType::Random:
        case ContainerType::Random2:
            condition_size = sizeof(RandomCondition);
            break;
        default:
            condition_size = 0;
            break;
        }
    }
}

void ResourceParamCreator::solveAboutGlobalProperty(RomResourceParam* rom_res_param, const ParamDefineTable* param_define, System* system)
{
    solveCommonResourceAboutGlobalProperty_(rom_res_param, system);
    
    for (u32 i {0}; i < rom_res_param->numUser; ++i)
        solveUserBinAboutGlobalProperty_(calcOffset<ResUserHeader>(rom_res_param->offsetTable[i]), param_define, system);
}

void ResourceParamCreator::createParamAndSolveResource(EditorResourceParam* editor_res_param, const sead::SafeString& editor_name, 
                                                       u8* buffer, u32 data_size, const ParamDefineTable* param_define, System* system)
{
    u8* dest {editor_res_param->binBuffer}; // UNUSED

    if (!editor_res_param->isInitialized) {
        editor_res_param->editorName.copy(editor_name);
        editor_res_param->binBuffer = new (system->getPrimaryHeap()) u8[data_size];
        editor_res_param->binBufferSize = data_size;
    }
    else if (editor_res_param->binBufferSize != data_size) {
        delete[] editor_res_param->binBuffer;
        editor_res_param->binBuffer = new (system->getPrimaryHeap()) u8[data_size];
        editor_res_param->binBufferSize = data_size;
    }

    sead::MemUtil::copy(editor_res_param->binBuffer, buffer, data_size);
    
    EditorHeader* header {reinterpret_cast<EditorHeader*>(editor_res_param->binBuffer)};
    u32 user_bin_pos = reinterpret_cast<u64>(header) + header->userBinPos;
    editor_res_param->pResUserHeader = calcOffset<ResUserHeader>(user_bin_pos);

    BinAccessor bin_accessor {header, param_define};
    
    createCommonResourceParam_(editor_res_param, &bin_accessor);

    if (system->debugOperationParamOR().getPrintFlag().isOnBit(0))
        dumpEditorResource_(editor_res_param, &bin_accessor, param_define, system->getPrimaryHeap());

    solveCommonResource_(editor_res_param, &bin_accessor);
    solveUserBin_(editor_res_param->pResUserHeader, editor_res_param, param_define);
    
    if (system->isGlobalPropFixed())
        solveAboutGlobalProperty(editor_res_param, param_define, system);

    editor_res_param->isInitialized = true;
}

void ResourceParamCreator::dumpEditorResource_(EditorResourceParam* editor_res_param,
                                               const BinAccessor* bin_accessor,
                                               const ParamDefineTable* param_define,
                                               sead::Heap* heap)
{
    dumpLine_(nullptr, "[XLink2] EditorBuffer dump\n");

    EditorHeader* editor_header{reinterpret_cast<EditorHeader*>(editor_res_param->binBuffer)};
    sead::FixedSafeString<64>* editor_name{&editor_res_param->editorName};

    dumpLine_(nullptr, "<< EditorHeader[%s] (addr:0x%x, size:%@) >>\n",
              editor_res_param->editorName.getBuffer(), editor_header, sizeof(EditorHeader));
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

    dumpCommonResourceFront_(editor_res_param, bin_accessor, true, nullptr);
    dumpUserBin_(0, *editor_name, editor_res_param->pResUserHeader, param_define, nullptr);
    dumpCommonResourceRear_(editor_res_param, bin_accessor, editor_res_param->binBufferSize, heap, false,
                            nullptr);
}

void ResourceParamCreator::solveAboutGlobalProperty(EditorResourceParam* editor_res_param, const ParamDefineTable* param_define, System* system)
{
    solveCommonResourceAboutGlobalProperty_(editor_res_param, system);
    solveUserBinAboutGlobalProperty_(editor_res_param->pResUserHeader, param_define, system);
}

void ResourceParamCreator::createUserBinParam(UserBinParam* user_bin_param, ResUserHeader* user_header, const ParamDefineTable*  param_define)
{
    *user_bin_param = {};
    user_bin_param->commonResourceParam = reinterpret_cast<CommonResourceParam*>(user_header);

    u32* local_prop_name_refs {reinterpret_cast<u32*>(user_header + 1)};
    if (user_header->numLocalProperty > 0)
        user_bin_param->pLocalPropertyNameRefTable = local_prop_name_refs;
    
    ResParam* user_params {reinterpret_cast<ResParam*>(local_prop_name_refs + user_header->numLocalProperty)};
    if (param_define->getNumUserParam() > 0)
        user_bin_param->userParamArray = user_params; 

    s16* sorted_asset_id_table {reinterpret_cast<s16*>(user_params + param_define->getNumUserParam())};
    if (user_header->numCallTable > 0)
        user_bin_param->pSortedAssetIdTable = sorted_asset_id_table;
    
    ResAssetCallTable* asset_ctb {reinterpret_cast<ResAssetCallTable*>(sorted_asset_id_table + user_header->numCallTable)};
    if (user_header->numCallTable & 1)
        asset_ctb = reinterpret_cast<ResAssetCallTable*>(sorted_asset_id_table + user_header->numCallTable + 1);

    if (user_header->numCallTable > 0)
        user_bin_param->pResAssetCallTable = asset_ctb;

    u32 container_table_pos = reinterpret_cast<u64>(asset_ctb + user_header->numCallTable);
    if (user_header->numCallTable != user_header->numAsset)
        user_bin_param->containerTablePos = container_table_pos; 

    ResActionSlot* action_slot_table {calcOffset<ResActionSlot>(reinterpret_cast<u64>(user_header) + user_header->triggerTablePos)};
    if (user_header->numResActionSlot > 0)
        user_bin_param->pResActionSlotTable = action_slot_table;
    
    ResAction* action_table {reinterpret_cast<ResAction*>(action_slot_table + user_header->numResActionSlot)};
    if (user_header->numResAction > 0)
        user_bin_param->pResActionTable = action_table;
    
    ResActionTrigger* action_trigger_table {reinterpret_cast<ResActionTrigger*>(action_table + user_header->numResAction)};
    if (user_header->numResActionTrigger > 0)
        user_bin_param->pResActionTriggerTable = action_trigger_table;
    
    ResProperty* property_table {reinterpret_cast<ResProperty*>(action_trigger_table + user_header->numResActionTrigger)};
    if (user_header->numResProperty > 0)
        user_bin_param->pResPropertyTable = property_table;
    
    ResPropertyTrigger* property_trigger_table {reinterpret_cast<ResPropertyTrigger*>(property_table + user_header->numResProperty)};
    if (user_header->numResPropertyTrigger > 0)
        user_bin_param->pResPropertyTriggerTable = property_trigger_table;
    
    ResAlwaysTrigger* always_trigger_table {reinterpret_cast<ResAlwaysTrigger*>(property_trigger_table + user_header->numResPropertyTrigger)};
    if (user_header->numResAlwaysTrigger > 0)
        user_bin_param->pResAlwaysTriggerTable = always_trigger_table;
}

void ResourceParamCreator::solveCommonResourceAboutGlobalProperty_(CommonResourceParam* common_res_param, System* system)
{
    for (u32 i {0}; i < common_res_param->numCurveTable; ++i) {
        ResCurveCallTable* curve_ctb_item {common_res_param->curveCallTable};
        if (curve_ctb_item[i].isPropGlobal != 0 && curve_ctb_item[i].localPropertyNameIdx == -1) {
            const char* prop_name {calcOffset<char>(curve_ctb_item[i].propName)};
            s32 global_property_idx {system->searchGlobalPropertyIndex(calcOffset<char>(curve_ctb_item[i].propName))};

            if (global_property_idx == -1) {
                const char* prop_name {calcOffset<char>(curve_ctb_item[i].propName)};
                system->addError(Error::Type::PropertyNotFound, nullptr, "property[%s(G)] in curve", prop_name);
            }
            else {
                curve_ctb_item[i].localPropertyNameIdx = global_property_idx;
            }
        }
    }
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

void ResourceParamCreator::dumpCommonResourceFront_(CommonResourceParam* common_res_param,
                                                    const BinAccessor* bin_accessor,
                                                    bool print_content,
                                                    sead::BufferedSafeString* dump_str)
{
    // ------------------------------------ResAssetParamTable--------------------------------------
    
    dumpLine_(dump_str, "<< ResAssetParamTable (addr:0x%x, size:print later) >>\n", 
            reinterpret_cast<u64>(common_res_param->assetParamTable));

            
    u32 not_default_param_num {0};
    u32 all_param_num {0};
    
    ResAssetParam* asset_param_table_start {common_res_param->assetParamTable};
    u64 asset_param_table_pos {reinterpret_cast<u64>(asset_param_table_start)};

    for (s32 i {0}; i < common_res_param->numResAssetParam; ++i) {
        auto* asset_param {reinterpret_cast<ResAssetParam*>(asset_param_table_pos)};
        if (print_content)
            dumpLine_(dump_str, "  [%d] mask: %lu\n", i, asset_param->mask.getDirect());

        auto* param {asset_param->params};
        asset_param_table_pos += 8;
        
        for (u32 j {0}; j < bin_accessor->numAssetParam; ++j) {
            if (asset_param->mask.isOnBit(static_cast<s32>(j))) {
                if (print_content)
                    dumpLine_(dump_str, "  [%d] param of bit[%d]: rawValue: %u (referenceType: %d, value: %d)\n", i, j, 
                                        param->rawValue, param->getRefType(), param->getValue());
                ++not_default_param_num;
                ++param;
                asset_param_table_pos += sizeof(ResParam);
            }
            else if (print_content) {
                dumpLine_(dump_str, "  [%d] param of bit[%d]: not exist(default value)\n", i, j);
            }
            ++all_param_num;
        }
    }

    if (!print_content)
        dumpLine_(dump_str, "  ...no content print.\n");

    dumpLine_(dump_str, "<< ResAssetParamTable finished(size:%d, allParamNum=%d, notDefaultParamNum=%d) >>\n",
              asset_param_table_pos - reinterpret_cast<u64>(asset_param_table_start), all_param_num, not_default_param_num);
    dumpLine_(dump_str, "\n");

    // -------------------------------ResTriggerOverwriteParamTable--------------------------------
    
    u32 overwrite_param_num {0};
    u32 all_overwrite_param_num {0};

    dumpLine_(dump_str, "<< ResTriggerOverwriteParamTable (addr:0x%x, size:print later) >>\n",
              bin_accessor->getTriggerOverwriteParamTablePos());

    u32 trigger_param_table_start {common_res_param->triggerOverwriteParamTablePos};
    s32 ow_param_table_pos {static_cast<s32>(trigger_param_table_start)};

    for (s32 i {0}; i < common_res_param->numResTriggerOverwriteParam; ++i) {
        auto* trigger_param {calcOffset<ResTriggerOverwriteParam>(ow_param_table_pos)};
        if (print_content)
            dumpLine_(dump_str, "  [%d] mask: %lu\n", i, trigger_param->mask.getDirect());

        auto* param {trigger_param->params};
        ow_param_table_pos += 4;

        for (s32 j {0}; j < bin_accessor->numTriggerParam; ++j) {
            if (trigger_param->mask.isOnBit(j)) {
                if (print_content)
                    dumpLine_(dump_str, "  [%d] param of bit[%d]: rawValue: %u (referenceType: %d, value: %d)\n", i, j, 
                            param->rawValue, param->getRefType(), param->getValue());
                ++overwrite_param_num;
                ++param;
                ow_param_table_pos += sizeof(ResParam);
            }
            else if (print_content) {
                dumpLine_(dump_str, "  [%d] param of bit[%d]: not exist(not overwritten)\n", i, j);
            }
            ++all_overwrite_param_num;
        }
    }
    
    if (!print_content)
        dumpLine_(dump_str, "  ...no content print.\n");

    dumpLine_(dump_str, "<< ResTriggerOverwriteParamTable finished(size:%d, allParamNum=%d, overwriteNum=%d) >>\n",
              ow_param_table_pos - trigger_param_table_start, all_overwrite_param_num, overwrite_param_num);
    dumpLine_(dump_str, "\n");

    // --------------------------------LocalPropertyNameRefTable-----------------------------------

    u32 size_local_property {common_res_param->numLocalPropertyNameRefTable * 8};
    dumpLine_(dump_str, "<< LocalPropertyNameRefTable (addr:0x%x, size:%d*%u=%u) >>\n",
              reinterpret_cast<u64>(common_res_param->localPropertyNameRefTable), 8,
              common_res_param->numLocalPropertyNameRefTable,
              size_local_property);

    if (print_content) {
        for (u32 i {0}; i < common_res_param->numLocalPropertyNameRefTable; ++i) {
            dumpLine_(dump_str, "  [%d] namePos=%d\n", i,
                        common_res_param->localPropertyNameRefTable[i]);
        }
    }
    else {
        dumpLine_(dump_str, "  ...no content print.\n");
    }
    dumpLine_(dump_str, "\n");

    // -------------------------------LocalPropertyEnumNameRefTable--------------------------------

    u32 size_local_enum_property {common_res_param->numLocalPropertyEnumNameRefTable * 8};
    dumpLine_(dump_str, "<< LocalPropertyEnumNameRefTable (addr:0x%x, size:%d*%u=%u) >>\n",
              reinterpret_cast<u64>(common_res_param->localPropertyEnumNameRefTable), 8,
              common_res_param->numLocalPropertyEnumNameRefTable,
              size_local_enum_property);

    if (print_content) {
        for (u32 i {0}; i < common_res_param->numLocalPropertyEnumNameRefTable; ++i) {
            dumpLine_(dump_str, "  [%d] enumNamePos=%d\n", i,
                        common_res_param->localPropertyEnumNameRefTable[i]);
        }
    }
    else {
        dumpLine_(dump_str, "  ...no content print.\n");
    }
    dumpLine_(dump_str, "\n");

    // -------------------------------------DirectValueTable---------------------------------------

    u32 size_direct_value {common_res_param->numDirectValueTable * 4};
    dumpLine_(dump_str, "<< DirectValueTable (addr:0x%x, size:%d*%u=%u) >>\n",
              reinterpret_cast<u64>(common_res_param->directValueTable), 4, common_res_param->numDirectValueTable,
              size_direct_value);

    if (print_content) {
        for (u32 i {0}; i < common_res_param->numDirectValueTable; ++i) {
            dumpLine_(dump_str, "  [%d] directvalue=%d\n", i,
                        common_res_param->directValueTable[i]);
        }
    }
    else {
        dumpLine_(dump_str, "  ...no content print.\n");
    }
    dumpLine_(dump_str, "\n");

    // -------------------------------------RandomCallTable----------------------------------------

    u32 size_random_ctb {common_res_param->numRandomTable * 8};
    dumpLine_(dump_str, "<< RandomCallTable (addr:0x%x, size:%d*%u=%u) >>\n",
              reinterpret_cast<u64>(common_res_param->randomCallTable), 8, common_res_param->numRandomTable,
              size_random_ctb);

    if (print_content) {
        for (u32 i {0}; i < common_res_param->numRandomTable; ++i) {
            dumpLine_(dump_str, "  [%d] minValue=%.4f, maxValue=%.4f\n", i,
                        common_res_param->randomCallTable[i].minValue,
                        common_res_param->randomCallTable[i].maxValue);
        }
    }
    else {
        dumpLine_(dump_str, "  ...no content print.\n");
    }
    dumpLine_(dump_str, "\n");

    // --------------------------------------CurveCallTable----------------------------------------

    u32 size_curve_ctb {common_res_param->numCurveTable * 20};
    dumpLine_(dump_str, "<< CurveCallTable (addr:0x%x, size:%d*%u=%u) >>\n",
              reinterpret_cast<u64>(common_res_param->curveCallTable), sizeof(ResCurveCallTable), common_res_param->numCurveTable,
              size_curve_ctb);

    if (print_content) {
        for (u32 i {0}; i < common_res_param->numCurveTable; ++i) {
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
    else {
        dumpLine_(dump_str, "  ...no content print.\n");
    }
    dumpLine_(dump_str, "\n");

    // -------------------------------------CurvePointTable----------------------------------------

    u32 size_curve_point {common_res_param->numCurvePointTable * 8};
    dumpLine_(dump_str, "<< CurvePointTable (addr:0x%x, size:%d*%u=%u) >>\n",
              reinterpret_cast<u64>(common_res_param->curvePointTable), 8, common_res_param->numCurvePointTable,
              size_curve_point);

    if (print_content) {
        for (u32 i {0}; i < common_res_param->numCurvePointTable; ++i) {
            dumpLine_(dump_str, "  [%d] x=%.4f, y=%.4f\n", i, 
                      common_res_param->curvePointTable[i].x,
                      common_res_param->curvePointTable[i].y);
        }
    }
    else {
        dumpLine_(dump_str, "  ...no content print.\n");
    }
    dumpLine_(dump_str, "\n");

    // -----------------------------------------ExRegion-------------------------------------------

    dumpLine_(dump_str, "<< ExRegion (addr:0x%x, size:unknown) >>\n",
              common_res_param->exRegionPos);

    if (print_content)
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
    u32 name_table_pos {bin_accessor->getNameTablePos()};
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
}  // namespace xlink2
