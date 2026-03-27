#include "xlink2/xlink2RandomContainer.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ResourceUtil.h"
#include "xlink2/xlink2UserResource.h"

namespace xlink2 {
RandomContainer::~RandomContainer() = default;

// WIP
bool RandomContainer::calc()
{
    auto* child {mpChild};
    bool result {child->calc()};
    if (result != CalcResult::Failure) {
        child->destroy();
        mpChild = nullptr;
        return assetFinished();
    }
    return CalcResult(!result);
}

bool RandomContainer::start()
{
    UserInstance* user_instance {mpEvent->getUserInstance()};
    ResContainerParam* param {ResourceUtil::getResContainerParam(*mpAssetCallTable)};
    s32 child_start_idx {param->childrenStartIndex};
    s32 child_end_idx {param->childrenEndIndex};

    f32 total_weight {0};
    UserResource* user_resource {user_instance->getUserResource()};

    bool condition {child_start_idx <= child_end_idx};
    for (s32 i {child_start_idx}; condition; ++i) {
        ResAssetCallTable* asset_ctb_item {user_resource->getAssetCallTableItem(i)};
        if (asset_ctb_item->conditionPos != 0) {
            auto* condition_param {solveOffset<ResRandomCondition>(asset_ctb_item->conditionPos)};
            total_weight += condition_param->weight;
        }
        condition = i < child_end_idx;
    }

    if (total_weight > 0) {
        f32 weight {0};
        auto* system {mpEvent->getUserInstance()->getUser()->getSystem()};
        f32 random_f32 {(system->getRandom()->getF32() * total_weight) + 0.0f};

        bool condition {child_end_idx >= child_start_idx};
        for (s32 j {child_start_idx}; condition; ++j) {
            ResAssetCallTable* asset_ctb_item {user_resource->getAssetCallTableItem(j)};
            if (asset_ctb_item->conditionPos != 0) {
                auto* condition_param {solveOffset<ResRandomCondition>(asset_ctb_item->conditionPos)};
                weight += condition_param->weight;
            
                if (random_f32 < weight)
                    return createChildContainer(*asset_ctb_item, user_instance, nullptr) != nullptr;
            }
            condition = j < child_end_idx;
        }
    }

    return false;
}

RandomContainer2::~RandomContainer2() = default;
} // namespace xlink2