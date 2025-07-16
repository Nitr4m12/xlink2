#pragma once

#include <prim/seadSafeString.h>

#include "xlink2/xlink2Types.h"

namespace xlink2 {
class PropertyDefinition {
public:
    PropertyDefinition() = default;
    PropertyDefinition(const char* name, PropertyType type, u8 unk)
        : mPropertyName(name), mType(type), _0(unk) {}

    virtual ~PropertyDefinition() = default;

    PropertyType getType() const { return mType; }
    const sead::FixedSafeString<64>* getPropertyName() const { return &mPropertyName; }

protected:
    sead::FixedSafeString<64> mPropertyName;
    PropertyType mType;
    u8 _0;
};
static_assert(sizeof(PropertyDefinition) == 0x68, "xlink2::PropertyDefinition size mismatch");

class F32PropertyDefinition : public PropertyDefinition {
public:
    ~F32PropertyDefinition() override;
    
private:
    f32 mMinValue;
    f32 mMaxValue;
};
static_assert(sizeof(F32PropertyDefinition) == 0x70, "xlink2::F32PropertyDefinition size mismatch");

class S32PropertyDefinition : public PropertyDefinition {
public:
    ~S32PropertyDefinition() override;
    
private:
    s32 mMinValue;
    s32 mMaxValue;
};
static_assert(sizeof(S32PropertyDefinition) == 0x70, "xlink2::S32PropertyDefinition size mismatch");

}  // namespace xlink2
