#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace xlink2 {
struct Error {
    enum class Type : u32 {
        None,
        DelayDisturbed,
        OtameshiEmitFailed,
        AssetPreviewFailed,
        EventPoolFull,
        OneTimeShouldBeClipNoneOrKill,
        HoldAssetFull,
        EmitterSetNotFound,
        AssetNotFound,
        BoneNotFound,
        GroupNotFound,	
        DRCSNotFound,	
        MtxSetTypeNotProgrammer,	
        RootMtxNotInput,	
        DataFormatError,	
        DataVersionError,	
        ResourceAccessFailed,	
        ActionNotFound,	
        ActionSlotNotFound,	
        PropertyNotFound,	
        InvalidContainer,	
        CommProtocolVersionError,	
        PropertyDefineError,	
        ParameterRangeError,	
        CustomParamAccessFailed,	
        CallWithoutSetup,	
        TargetOverSoundLimit,	
        EventHasMultipleAsset,	
        ListToGetterIsFull,	
        PropertyOutOfRange,	
        InvalidPropertyType,	
        OutOfMemory,	
        InterruptCalc,	
        TooManyBlendChildren,	
        MultipleSameNameKeys,	
        EmitInvalidEmitterSet,	
        Etc,	
        UnknownError,	
    };

    Type type;
    sead::FixedSafeString<320> fixedString1;
    sead::FixedSafeString<256> fixedString2;
    u32 _0;
};
}  // namespace xlink2