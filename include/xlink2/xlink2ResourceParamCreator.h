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
class System;

namespace ResourceParamCreator {
class BinAccessor {
public:
    BinAccessor(ResourceHeader*, ParamDefineTable const*);
    BinAccessor(EditorHeader*, ParamDefineTable const*);

    ResourceHeader* mResourceHeader;
    EditorHeader* mEditorHeader;
    s32 mBinStart;
    s32 mBinEnd;
    u32 mUserParamNum;
    u32 mAssetParamNum;
};

void createParamAndSolveResource(RomResourceParam*, void*, ParamDefineTable const*, System*);
void createCommonResourceParam_(CommonResourceParam*, BinAccessor*);
void dumpRomResource(ResourceHeader*, RomResourceParam*, BinAccessor const*,
                     ParamDefineTable const*, sead::Heap*, bool, sead::BufferedSafeString*);

void solveCommonResource_(CommonResourceParam*, BinAccessor*);
void solveUserBin_(ResUserHeader*, CommonResourceParam*, ParamDefineTable const*);
void solveAboutGlobalProperty(RomResourceParam*, ParamDefineTable const*, System*);

void createParamAndSolveResource(EditorResourceParam*, sead::SafeString const&, u8*, u32,
                                 ParamDefineTable const*, System*);
void dumpEditorResource(EditorResourceParam*, BinAccessor const*, ParamDefineTable const*,
                        sead::Heap*);
void solveAboutGlobalProperty(EditorResourceParam*, ParamDefineTable const*, System*);

void createUserBinParam(UserBinParam*, ResUserHeader*, ParamDefineTable const*);
void solveCommonResourceAboutGlobalProperty_(CommonResourceParam*, System*);
void solveUserBinAboutGlobalProperty(ResUserHeader*, ParamDefineTable const*, System*);

void dumpLine_(sead::BufferedSafeString*, char const*, ...);

void dumpCommonResourceFront_(CommonResourceParam*, BinAccessor const*, bool,
                              sead::BufferedSafeString*);
void dumpUserBin_(u32, sead::SafeString const&, ResUserHeader*, ParamDefineTable const*,
                  sead::BufferedSafeString*);
void dumpCommonResourceRear(CommonResourceParam*, BinAccessor const*, u32, sead::Heap*, bool,
                            sead::BufferedSafeString*);
};  // namespace ResourceParamCreator
}  // namespace xlink2