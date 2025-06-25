#include "xlink2/xlink2SequenceContainer.h"
#include "xlink2/xlink2ResourceUtil.h"
#include "xlink2/xlink2Util.h"

namespace xlink2 {
bool SequenceContainer::callNextChildSequence_()
{
    ResContainerParam* param {ResourceUtil::getResContainerParam(*mpAssetCallTable)};

    s32 start {param->childrenStartIndex};
    s32 end {param->childrenEndIndex};
    do {
        if (mSequenceIndex >= end - start)
            return false;

        ++mSequenceIndex;
    } while (!callChildSequence_(mSequenceIndex));

    return true;
}

bool SequenceContainer::callChildSequence_(s32 idx)
{
    UserInstance* user_instance {mpEvent->getUserInstance()};
    ResContainerParam* param {ResourceUtil::getResContainerParam(*mpAssetCallTable)};
    s32 child_start_idx {param->childrenStartIndex};
    
    UserResource* user_resource {user_instance->getUser()->getUserResource()};
    ResAssetCallTable* asset_ctb_item {user_resource->getAssetCallTableItem(child_start_idx + idx)};
    
    Event* event {mpEvent};

    const char* container_name {user_instance->getContainerTypeName(*mpAssetCallTable)->cstr()};
    const char* key_name {calcOffset<char>(mpAssetCallTable->keyNamePos)};
    
    const char* container_child_name {user_instance->getContainerTypeName(*asset_ctb_item)->cstr()};
    const char* key_name_child {calcOffset<char>(asset_ctb_item->keyNamePos)};

    user_instance->printLogContainerSelect(*event, "%s[%s] -> %s[%s] (idx=%d)", container_name, key_name, container_child_name, key_name_child, idx);

    return createChildContainer_(*asset_ctb_item, nullptr);

}
}