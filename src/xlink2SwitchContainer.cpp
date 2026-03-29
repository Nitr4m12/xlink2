#include "xlink2/xlink2SwitchContainer.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2UserResource.h"

namespace xlink2 {
SwitchContainer::~SwitchContainer() = default;

// NON-MATCHING
bool SwitchContainer::calc()
{
    bool check1 {false};
    if (mpEvent->getBitFlag().isOffBit(4)) {
        auto& accessor {mpEvent->getUserInstance()->getUser()->getUserResource()->getAccessor()};
        bool need_observe {accessor.isNeedObserve(*mpAssetCallTable)};
        bool bit_3_on {mpEvent->getBitFlag().isOnBit(3)};
        check1 = need_observe && !bit_3_on;

        // if goes here, not sure on the order of checks, so it's left out for now
        {
            auto* asset_ctb {getConditionMatchChildCallTable_()};
            if (mpChild != nullptr) {
                if (mpChild->getAssetCallTable() != asset_ctb) {
                    mpChild->fadeBySystem();
                    mpChild->destroy();
                    mpChild = nullptr;
                    
                    if (asset_ctb != nullptr)
                        createChildContainer_(*asset_ctb, nullptr);
                }
            }
            else if (asset_ctb != nullptr) {
                createChildContainer_(*asset_ctb, nullptr);
            }
        }

    }

    bool check2 {true};
    if (mpChild != nullptr) {
        if (mpChild->calc()) {
            mpChild->destroy();
            mpChild = nullptr;
            check2 = assetFinished();
        }
        else {
            check2 = false;
        }
    }

    return !check1 && check2;
}

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

void SwitchContainer::printChildSelect_([[maybe_unused]] const ResAssetCallTable* asset_ctb) const
{
#ifdef SEAD_DEBUG
#endif 
}
} // namespace xlink2