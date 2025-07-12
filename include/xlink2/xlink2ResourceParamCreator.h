#pragma once

#include "prim/seadSafeString.h"

#include "xlink2/xlink2ActionTriggerCtrl.h"
#include "xlink2/xlink2CommonResourceParam.h"
#include "xlink2/xlink2EditorHeader.h"
#include "xlink2/xlink2EditorResourceParam.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2ResUserHeader.h"
#include "xlink2/xlink2ResourceHeader.h"
#include "xlink2/xlink2RomResourceParam.h"
#include "xlink2/xlink2UserBinParam.h"

namespace xlink2 {
class System;

class ResourceParamCreator {
public:
    class BinAccessor {
    public:
        BinAccessor(ResourceHeader*, const ParamDefineTable*);
        BinAccessor(EditorHeader*, const ParamDefineTable*);

        ResourceHeader* pResourceHeader {};
        EditorHeader* pEditorHeader {};
        u32 binStart;
        u32 assetsStart;
        u32 numAssetParam;
        u32 numTriggerParam;

        u32 getNumResParam() const 
        {
            return pResourceHeader != nullptr ? pResourceHeader->numResParam : pEditorHeader->numResParam;
        }

        u32 getNumResAssetParam() const
        {
            return pResourceHeader != nullptr ? pResourceHeader->numResAssetParam : pEditorHeader->numResAssetParam;
        }

        u32 getNumResTriggerOverwriteParam() const
        {
            return pResourceHeader != nullptr ? pResourceHeader->numResTriggerOverwriteParam : pEditorHeader->numResTriggerOverwriteParam;
        }

        u32 getNumLocalPropertyNameRefTable() const
        {
            return pResourceHeader != nullptr ? pResourceHeader->numLocalPropertyNameRefTable : pEditorHeader->numLocalPropertyNameRefTable;
        }

        u32 getNumLocalPropertyEnumNameRefTable() const
        {
            return pResourceHeader != nullptr ? pResourceHeader->numLocalPropertyEnumNameRefTable : pEditorHeader->numLocalPropertyEnumNameRefTable;
        }

        u32 getNumDirectValueTable() const
        {
            return pResourceHeader != nullptr ? pResourceHeader->numDirectValueTable : pEditorHeader->numDirectValueTable;
        }

        u32 getNumRandomTable() const
        {
            return pResourceHeader != nullptr ? pResourceHeader->numRandomTable : pEditorHeader->numRandomTable;
        }

        u32 getNumCurveTable() const
        {
            return pResourceHeader != nullptr ? pResourceHeader->numCurveTable : pEditorHeader->numCurveTable;
        }

        u32 getNumCurvePointTable() const
        {
            return pResourceHeader != nullptr ? pResourceHeader->numCurvePointTable : pEditorHeader->numCurvePointTable;
        }

        u32 getTriggerOverwriteParamTablePos() const
        {
            return pResourceHeader != nullptr ? pResourceHeader->triggerOverwriteParamTablePos : pEditorHeader->triggerOverwriteParamTablePos;
        }

        u32 getLocalPropertyNameRefTablePos() const
        {
            return pResourceHeader != nullptr ? pResourceHeader->localPropertyNameRefTablePos : pEditorHeader->localPropertyNameRefTablePos;
        }

        u32 getExRegionPos() const
        {
            return pResourceHeader != nullptr ? pResourceHeader->exRegionPos : pEditorHeader->exDataRegionPos;
        }

        u32 getConditionTablePos() const
        {
            return pResourceHeader != nullptr ? pResourceHeader->conditionTablePos : pEditorHeader->conditionTablePos;
        }

        u32 getNameTablePos() const
        {
            return pResourceHeader != nullptr ? pResourceHeader->nameTablePos : pEditorHeader->nameTablePos;
        }
    };

    static void createParamAndSolveResource(RomResourceParam*, void*, const ParamDefineTable*,
                                            System*);
    static void createCommonResourceParam_(CommonResourceParam*, BinAccessor*);
    static void dumpRomResource_(ResourceHeader*, RomResourceParam*, const BinAccessor*,
                                 const ParamDefineTable*, sead::Heap*, bool,
                                 sead::BufferedSafeString*);

    static void solveCommonResource_(CommonResourceParam*, BinAccessor*);
    static void solveUserBin_(ResUserHeader*, CommonResourceParam*, const ParamDefineTable*);
    static void solveAboutGlobalProperty(RomResourceParam*, const ParamDefineTable*, System*);

    static void createParamAndSolveResource(EditorResourceParam*, const sead::SafeString&, u8*, u32, const ParamDefineTable*, System*);
    static void dumpEditorResource_(EditorResourceParam*, const BinAccessor*,
                                    const ParamDefineTable*, sead::Heap*);
    static void solveAboutGlobalProperty(EditorResourceParam*, const ParamDefineTable*, System*);

    static void createUserBinParam(UserBinParam*, ResUserHeader*, const ParamDefineTable*);
    static void solveCommonResourceAboutGlobalProperty_(CommonResourceParam*, System*);
    static void solveUserBinAboutGlobalProperty_(ResUserHeader*, const ParamDefineTable*, System*);

    static void dumpLine_(sead::BufferedSafeString*, const char*, ...);

    static void dumpCommonResourceFront_(CommonResourceParam*, const BinAccessor*, bool,
                                         sead::BufferedSafeString*);
    static void dumpUserBin_(u32, const sead::SafeString&, ResUserHeader*, const ParamDefineTable*,
                             sead::BufferedSafeString*);
    static void dumpCommonResourceRear_(CommonResourceParam*, const BinAccessor*, u32, sead::Heap*,
                                        bool, sead::BufferedSafeString*);

private:
    static void solveActionTriggerTable(ResActionTrigger* action_trigger_table, ResAssetCallTable* asset_ctb, 
                                        const ResUserHeader* user_header, CommonResourceParam* common_res_param)
    {
        for (u32 i {0}; i < user_header->numResActionTrigger; ++i) {
            ResActionTrigger* action_trigger {&action_trigger_table[i]};
            action_trigger->assetCtbPos += reinterpret_cast<u64>(asset_ctb);
            action_trigger->overwriteParamPos = action_trigger->overwriteParamPos != -1 ? action_trigger->overwriteParamPos + common_res_param->triggerOverwriteParamTablePos : 0;

            if (ActionTriggerCtrl::getActionTriggerType_(*action_trigger) == TriggerType::None)
                action_trigger->startFrame += common_res_param->nameTablePos;
        }
    }

    static void solvePropertyTriggerTable(ResPropertyTrigger* property_trigger_table, ResAssetCallTable* asset_ctb, 
                                          const ResUserHeader* user_header, CommonResourceParam* common_res_param)
    {
        for (u32 i {0}; i < user_header->numResPropertyTrigger; ++i) {
            ResPropertyTrigger* property_trigger {&property_trigger_table[i]};
            property_trigger->assetCtbPos += reinterpret_cast<u64>(asset_ctb);
            property_trigger->condition = property_trigger->condition != -1 ? property_trigger->condition + common_res_param->conditionTablePos : 0;
            property_trigger->overwriteParamPos = property_trigger->overwriteParamPos != -1 ? property_trigger->overwriteParamPos + common_res_param->triggerOverwriteParamTablePos : 0;
        }
    }

    static void solveAlwaysTriggerTable(ResAlwaysTrigger* always_trigger_table, ResAssetCallTable* asset_ctb, 
                                        const ResUserHeader* user_header, CommonResourceParam* common_res_param)
    {
        for (u32 i {0}; i < user_header->numResAlwaysTrigger; ++i) {
            ResAlwaysTrigger* always_trigger {&always_trigger_table[i]};
            always_trigger->assetCtbPos += reinterpret_cast<u64>(asset_ctb);
            always_trigger->overwriteParamPos = always_trigger->overwriteParamPos != -1 ? always_trigger->overwriteParamPos + common_res_param->triggerOverwriteParamTablePos : 0;
        }
    }
};
}  // namespace xlink2