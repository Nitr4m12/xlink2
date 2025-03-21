#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

#include "xlink2/xlink2PropertyType.h"

namespace xlink2 {
class PropertyDefinition {
public:
    virtual ~PropertyDefinition();

    PropertyType getType() const { return mType; }
    sead::FixedSafeString<64>* getPropertyName() { return &mPropertyName; }

protected:
    sead::FixedSafeString<64> mPropertyName;
    PropertyType mType;
    u8 _0;
};
static_assert(sizeof(PropertyDefinition) == 0x68, "Wrong size for 'xlink2::PropertyDefinition'");

class F32PropertyDefinition : public PropertyDefinition {
public:
    ~F32PropertyDefinition() override;
    
private:
    f32 mMinValue;
    f32 mMaxValue;
};
static_assert(sizeof(F32PropertyDefinition) == 0x70, "Wrong size for 'xlink2::F32PropertyDefinition'");

class S32PropertyDefinition : public PropertyDefinition {
public:
    ~S32PropertyDefinition() override;
    
private:
    s32 mMinValue;
    s32 mMaxValue;
};
static_assert(sizeof(S32PropertyDefinition) == 0x70, "Wrong size for 'xlink2::S32PropertyDefinition'");

}  // namespace xlink2
