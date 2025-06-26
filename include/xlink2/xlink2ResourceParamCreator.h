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
        BinAccessor(ResourceHeader*, ParamDefineTable const*);
        BinAccessor(EditorHeader*, ParamDefineTable const*);

        ResourceHeader* mResourceHeader;
        EditorHeader* mEditorHeader;
        u32 mBinStart;
        u32 mAssetsStart;
        u32 mNumUserParam;
        u32 mNumAssetParam;
    };

    static void createParamAndSolveResource(RomResourceParam*, void*, ParamDefineTable const*,
                                            System*);
    static void createCommonResourceParam_(CommonResourceParam*, BinAccessor*);
    static void dumpRomResource_(ResourceHeader*, RomResourceParam*, BinAccessor const*,
                                 ParamDefineTable const*, sead::Heap*, bool,
                                 sead::BufferedSafeString*);

    static void solveCommonResource_(CommonResourceParam*, BinAccessor*);
    static void solveUserBin_(ResUserHeader*, CommonResourceParam*, ParamDefineTable const*);
    static void solveAboutGlobalProperty(RomResourceParam*, ParamDefineTable const*, System*);

    static void createParamAndSolveResource(EditorResourceParam*, sead::SafeString const&, u8*, u32,
                                            ParamDefineTable const*, System*);
    static void dumpEditorResource_(EditorResourceParam*, BinAccessor const*,
                                    ParamDefineTable const*, sead::Heap*);
    static void solveAboutGlobalProperty(EditorResourceParam*, ParamDefineTable const*, System*);

    static void createUserBinParam(UserBinParam*, ResUserHeader*, ParamDefineTable const*);
    static void solveCommonResourceAboutGlobalProperty_(CommonResourceParam*, System*);
    static void solveUserBinAboutGlobalProperty(ResUserHeader*, ParamDefineTable const*, System*);

    static void dumpLine_(sead::BufferedSafeString*, const char*, ...);

    static void dumpCommonResourceFront_(CommonResourceParam*, BinAccessor const*, bool,
                                         sead::BufferedSafeString*);
    static void dumpUserBin_(u32, sead::SafeString const&, ResUserHeader*, ParamDefineTable const*,
                             sead::BufferedSafeString*);
    static void dumpCommonResourceRear_(CommonResourceParam*, BinAccessor const*, u32, sead::Heap*,
                                        bool, sead::BufferedSafeString*);
};
}  // namespace xlink2