#include "xlink2/xlink2BlendContainer.h"
#include "prim/seadSafeString.h"
#include "xlink2/xlink2ContainerBase.h"
#include "xlink2/xlink2ResAssetCallTable.h"
#include "xlink2/xlink2ResContainerParam.h"
#include "xlink2/xlink2ResourceUtil.h"
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
    ResourceUtil::getResContainerParam(mpAssetCallTable);
    return true;
}

bool BlendContainer::callAllChildContainer_() 
{
    bool b1;
    UserInstance* user_instance {mpEvent->getUserInstance()};
    ResContainerParam* param {ResourceUtil::getResContainerParam(mpAssetCallTable)};
    if (param->childrenEndIndex < param->childrenStartIndex) {
        b1 = false;
    }
    else {
        ContainerBase* container {nullptr};
        ContainerBase* childContainer {nullptr};
        bool b2 {true};
        u32 i {0};
        UserResource* user_resource {user_instance->getUser()->getUserResource()};
        s32 j{param->childrenStartIndex};
        while (b2) {

            const char* container_type_name {user_instance->getContainerTypeName(*mpAssetCallTable)->cstr()};
            char* key_name {calcOffset<char>(mpAssetCallTable->keyNamePos)};

            ResAssetCallTable* asset_call_item {user_resource->getAssetCallTableItem(j)};
            const char* other_container_name {user_instance->getContainerTypeName(*asset_call_item)->cstr()};
            char* other_key_name {calcOffset<char>(asset_call_item->keyNamePos)};

            user_instance->printLogContainerSelect(*mpEvent, "%s[%s] -> %s[%s] (idx=%d)", container_type_name, key_name, other_container_name, other_key_name, i);
            childContainer = createChildContainer_(*asset_call_item, container);
            if (childContainer)
                container = childContainer;
            b2 = b2 | (container != nullptr);
            ++i;
            b1 = j < param->childrenEndIndex;
            ++j;
        }
    }
    return b1;
}
}  // namespace xlink2
