#include <xlink2/xlink2PropertyTriggerCtrl.h>

#include <xlink2/xlink2EnumPropertyDefinition.h>
#include <xlink2/xlink2ModelTriggerConnection.h>
#include <xlink2/xlink2UserResource.h>
#include <xlink2/xlink2Util.h>

namespace xlink2 {
// NON_MATCHING
PropertyTriggerCtrl::PropertyTriggerCtrl(UserInstance* user_instance,
                                         sead::Buffer<ModelTriggerConnection>* mtc_buffer,
                                         s32 property_index, bool is_global_property,
                                         const ResProperty* res_property, ResMode mode)
    : TriggerCtrl(user_instance, mtc_buffer), mResProperty {res_property},
      mPropertyIndex {property_index}, mIsGlobalProperty {is_global_property}
{
    const PropertyDefinition* prop_define {};
    if (is_global_property) {
        prop_define = user_instance->getUser()->getSystem()->getPropertyDefinition(mPropertyIndex);
        is_global_property = mIsGlobalProperty;
        user_instance = mUserInstance;
    }
    else {
        prop_define = user_instance->getUser()->getPropertyDefinition(property_index);
    }

    if (is_global_property)
        mPropertyValue = user_instance->getUser()->getSystem()->getPropertyValue(mPropertyIndex);
    else
        mPropertyValue = user_instance->getPropertyValue(property_index);

    if (mResProperty->isGlobal || prop_define->getType() != PropertyType::Enum)
        return;

    auto* enum_prop_define {static_cast<const EnumPropertyDefinition*>(prop_define)};
    s32 trigger_start_idx {mResProperty->triggerStartIdx};
    s32 trigger_end_idx {mResProperty->triggerEndIdx};
    auto* resource_param {mUserInstance->getUserResource()->getParam(mode)};

    for (s32 i {trigger_start_idx - 1}; i < trigger_end_idx; ++i) {
        s32 condition_offset {resource_param->userBinParam.pResPropertyTriggerTable[i].condition};
        auto* condition_param {solveOffset<ResSwitchCondition>(condition_offset)};

        const CommonResourceParam* common_param {resource_param->pCommonResourceParam};
        s32 enum_name_idx {condition_param->localPropertyEnumNameIdx};
        u32 enum_name_offset {common_param->localPropertyEnumNameRefTable[enum_name_idx]};
        const char* enum_name {solveOffset<const char>(enum_name_offset)};
        getModelTriggerConnection_(i)->entryValue =
            enum_prop_define->searchEntryValueByKey(enum_name);
    }
}

// NON_MATCHING: virtual table is not being accessed
PropertyTriggerCtrl::~PropertyTriggerCtrl() = default;

void PropertyTriggerCtrl::reset()
{
    mPropertyValue.valueInt = 0;
    _2 = true;
    TriggerCtrl::resetIsOnceCheck_();
}
}  // namespace xlink2