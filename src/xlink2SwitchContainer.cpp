#include "xlink2/xlink2SwitchContainer.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2UserResource.h"

namespace xlink2 {
SwitchContainer::~SwitchContainer() = default;

bool SwitchContainer::start_(const ResAssetCallTable* asset_ctb)
{
    if (asset_ctb == nullptr) {
        UserInstance* user_instance {mpEvent->getUserInstance()};
        auto& accessor {user_instance->getUserResource()->getAccessor()};
        bool need_observe {accessor.isNeedObserve(*mpAssetCallTable)};
        u32 bit_flag {mpEvent->getBitFlag().getDirect()};
        if (!need_observe || bit_flag & 8) {
            const char* key_name {solveOffset<const char>(mpAssetCallTable->keyNamePos)};
            user_instance->printLogEmitFailed(*mpEvent, "switch container[%s] doesn't select child", key_name);
            return false;
        }
        
        return true;
    }

    return createChildContainer_(*asset_ctb, nullptr) != nullptr;
}

bool SwitchContainer::start()
{
    return start_(getConditionMatchChildCallTable_());
}
} // namespace xlink2