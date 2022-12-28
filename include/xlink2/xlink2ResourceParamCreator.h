#pragma once

#include "prim/seadSafeString.h"
#include "xlink2/xlink2CommonResourceParam.h"
#include "xlink2/xlink2EditorHeader.h"
#include "xlink2/xlink2EditorResourceParam.h"
#include "xlink2/xlink2ParamDefineTable.h"
#include "xlink2/xlink2ResUserHeader.h"
#include "xlink2/xlink2ResourceHeader.h"
#include "xlink2/xlink2RomResourceParam.h"
#include "xlink2/xlink2System.h"
#include "xlink2/xlink2UserBinParam.h"

namespace xlink2 {
class ResourceParamCreator {
public:
    class BinAccessor {
    public:
        BinAccessor(ResourceHeader*, ParamDefineTable const*);
        BinAccessor(EditorHeader*, ParamDefineTable const*);

    private:
    };

    void createCommonResourceParam(CommonResourceParam*, BinAccessor*);
    void createParamAndSolveResource(RomResourceParam*, void*, ParamDefineTable const*, System*);
    void createParamAndSolveResource(EditorResourceParam*, sead::SafeString const&, u8*, u32,
                                     ParamDefineTable const*, System*);
    void createUserBinParam(UserBinParam*, ResUserHeader*, ParamDefineTable const*);

    void dumpCommonResourceFront(CommonResourceParam*, BinAccessor const*, bool,
                                 sead::BufferedSafeString*);
    void dumpCommonResourceRear(CommonResourceParam*, BinAccessor const*, u32, sead::Heap*, bool,
                                sead::BufferedSafeString*);
    void dumpEditorResource(EditorResourceParam*, BinAccessor const*, ParamDefineTable const*,
                            sead::Heap*);
    void dumpLine(sead::BufferedSafeString*, char const*, ...);
    void dumpRomResource(ResourceHeader*, RomResourceParam*, BinAccessor const*,
                         ParamDefineTable const*, sead::Heap*, bool, sead::BufferedSafeString*);
    void dumpUserBin(u32, sead::SafeString const&, ResUserHeader*, ParamDefineTable const*,
                     sead::BufferedSafeString*);

    void solveAboutGlobalProperty(RomResourceParam*, ParamDefineTable const*, System*);
    void solveAboutGlobalProperty(EditorResourceParam*, ParamDefineTable const*, System*);
    void solveCommonResource(CommonResourceParam*, BinAccessor*);
    void solveCommonResourceAboutGlobalProperty(CommonResourceParam*, System*);
    void solveUserBin(ResUserHeader*, CommonResourceParam*, ParamDefineTable const*);
    void solveUserBinAboutGlobalProperty(ResUserHeader*, ParamDefineTable const*, System*);

private:
};
}  // namespace xlink2