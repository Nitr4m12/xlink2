#pragma once

#include "prim/seadSafeString.h"

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

        ResourceHeader* mResourceHeader;
        EditorHeader* mEditorHeader;
        u32 mBinStart;
        u32 mAssetsStart;
        u32 mNumAssetParam;
        u32 mNumUserParam;
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
    static void solveUserBinAboutGlobalProperty(ResUserHeader*, const ParamDefineTable*, System*);

    static void dumpLine_(sead::BufferedSafeString*, const char*, ...);

    static void dumpCommonResourceFront_(CommonResourceParam*, const BinAccessor*, bool,
                                         sead::BufferedSafeString*);
    static void dumpUserBin_(u32, const sead::SafeString&, ResUserHeader*, const ParamDefineTable*,
                             sead::BufferedSafeString*);
    static void dumpCommonResourceRear_(CommonResourceParam*, const BinAccessor*, u32, sead::Heap*,
                                        bool, sead::BufferedSafeString*);
};
}  // namespace xlink2