#include "xlink2/xlink2User.h"
#include "prim/seadSafeString.h"

namespace xlink2 {

System* User::getSystem() const {
    return mUserResource->getSystem();
}

u64 User::searchPropertyIndex(const char* name) const {
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
}  // namespace xlink2
