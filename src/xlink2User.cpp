#include "xlink2/xlink2User.h"
#include "prim/seadSafeString.h"

namespace xlink2 {

System* User::getSystem() const 
{
    return mUserResource->getSystem();
}

s32 User::calcNumActiveInstance() const
{
    s32 num_active_instance {0};
    for (auto& user_instance : mUserInstanceList) {
        num_active_instance += user_instance.getBitFlag().isOffBit(1);
    }

    return num_active_instance;
}

u64 User::searchPropertyIndex(const char* name) const 
{
    u16 num_local_prop = mNumLocalProp;
    if (num_local_prop != 0) {
        for (u64 i{0}; i < num_local_prop; ++i) {
            PropertyDefinition* property_definition = mPropertyDefinitionTable[i];
            if (property_definition != nullptr) {
                sead::FixedSafeString<64>* prop_name = property_definition->getPropertyName();
                int result = strcmp(name, prop_name->getBuffer());
                if (result == 0)
                    return i;
            }
        }
        num_local_prop = mNumLocalProp;
    }

    return 0xFFFFFFFF;
}

void User::beginOtameshi() 
{
    for (auto& user_instance : mUserInstanceList) {
        user_instance.fadeOrKillOtameshi(true);
        user_instance.freeEventIfFadeOrKillCalled();
    }
}
}  // namespace xlink2
