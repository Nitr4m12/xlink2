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
    if (param->childrenEndIndex > param->childrenStartIndex)
        return false;
    ContainerBase* container {nullptr};
    ContainerBase* childContainer {nullptr};
    bool b2 {false};
    // u32 i {0};
    UserResource* user_resource {user_instance->getUser()->getUserResource()};
    // s32 j{param->childrenStartIndex};
    for (s32 i {0}, j {param->childrenStartIndex}; i < param->childrenEndIndex; ++i, ++j) {
        ResAssetCallTable* asset_call_item {user_resource->getAssetCallTableItem(j)};
        
        const char* container_type_name {user_instance->getContainerTypeName(*mpAssetCallTable)->cstr()};
        char* key_name {calcOffset<char>(mpAssetCallTable->keyNamePos)};

        const char* other_container_name {user_instance->getContainerTypeName(*asset_call_item)->cstr()};
        char* other_key_name {calcOffset<char>(asset_call_item->keyNamePos)};


s8 BlendContainer::calc()
{
    ContainerBase* next {mpChild};
    ContainerBase* current {nullptr};
    bool finished {true};

    for (ContainerBase* previous {current}; next != nullptr; previous = current) {
        while (next != nullptr) {
            current = next;
            next = current->getNext();
            if (!(current->calc() & 1)) {
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

    if (finished == 0)
        return 0;

    return assetFinished();
}
}  // namespace xlink2
