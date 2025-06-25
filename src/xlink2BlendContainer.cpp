#include "xlink2/xlink2BlendContainer.h"
#include "xlink2/xlink2ResourceUtil.h"
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
    s32 child_start_idx {param->childrenStartIndex};
    ContainerBase* temp_child{};

    bool ret_val {false};

    for (s32 i {child_start_idx}, j{0}; i <= param->childrenEndIndex; ++i, ++j) {
        ResAssetCallTable* asset_ctb_item {user_instance->getUser()->getUserResource()->getAssetCallTableItem(j)};
        
        Event* event {mpEvent};

        const char* container_name {user_instance->getContainerTypeName(*mpAssetCallTable)->cstr()};
        const char* key_name {calcOffset<char>(mpAssetCallTable->keyNamePos)};
        
        const char* container_name_child {user_instance->getContainerTypeName(*asset_ctb_item)->cstr()};
        const char* key_name_child {calcOffset<char>(asset_ctb_item->keyNamePos)};

        user_instance->printLogContainerSelect(*event, "%s[%s] -> %s[%s] (idx=%d)", container_name, key_name, container_name_child, key_name_child, j);

        ContainerBase* child_container {createChildContainer_(*asset_ctb_item, temp_child)};
        if (child_container != nullptr)
            temp_child = child_container;

        if (temp_child != nullptr)
            return true;
        // ret_val = ret_val | (temp_child != nullptr);
    }

    return false;


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
