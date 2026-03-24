#include "xlink2/xlink2BlendContainer.h"

#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ResourceUtil.h"
#include "xlink2/xlink2UserInstance.h"
#include "xlink2/xlink2UserResource.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
BlendContainer::~BlendContainer() = default;

bool BlendContainer::start()
{
    return callAllChildContainer_();
}

bool BlendContainer::initialize(Event* event, const ResAssetCallTable& asset_call_table)
{
    ContainerBase::initialize(event, asset_call_table);
    ResourceUtil::getResContainerParam(*mpAssetCallTable);
    return true;
}

// WIP
bool BlendContainer::callAllChildContainer_() 
{
    UserInstance* user_instance {mpEvent->getUserInstance()};
    ResContainerParam* param {ResourceUtil::getResContainerParam(*mpAssetCallTable)};
    s32 child_end_idx {param->childrenEndIndex};

    ContainerBase* tmp_base {};

    bool ret_val {};

    bool condition {param->childrenEndIndex > param->childrenStartIndex};
    for (s32 i {param->childrenStartIndex}, j {0}; condition; ++i, ++j) {
        ResAssetCallTable* asset_ctb_item {user_instance->getUser()->getUserResource()->getAssetCallTableItem(i)};
        
        Event* event {mpEvent};

        const char* container_name {user_instance->getContainerTypeName(*mpAssetCallTable).cstr()};
        const char* key_name {solveOffset<char>(mpAssetCallTable->keyNamePos)};
        
        const char* container_name_child {user_instance->getContainerTypeName(*asset_ctb_item).cstr()};
        const char* key_name_child {solveOffset<char>(asset_ctb_item->keyNamePos)};

        user_instance->printLogContainerSelect(*event, "%s[%s] -> %s[%s] (idx=%d)", container_name, key_name, container_name_child, key_name_child, j);

        ContainerBase* child_container {createChildContainer_(*asset_ctb_item, tmp_base)};
        if (child_container != nullptr)
            tmp_base = child_container;

        ret_val = ret_val | (child_container != nullptr);

        condition = i < child_end_idx;
    }

    return ret_val;
}

ContainerBase::CalcResult BlendContainer::calc()
{
    ContainerBase* next {mpChild};
    ContainerBase* current {nullptr};
    bool finished {true};

    for (ContainerBase* previous {current}; next != nullptr; previous = current) {
        while (next != nullptr) {
            current = next;
            next = current->getNext();
            if (!(current->calc() & CalcResult::Success)) {
                finished = false;
                break;
            }
            if (previous != nullptr)
                previous->setNext(next);
            else
                mpChild = next;
            current->destroy();
        }
    }

    if (!finished)
        return CalcResult::Failure;

    return assetFinished();
}
}  // namespace xlink2
