#include "xlink2/xlink2ResourceUtil.h"

namespace xlink2::ResourceUtil {
TriggerType getActionTriggerType(ResActionTrigger const& action_trigger) {
    u16 flag{action_trigger.flag};

    if ((flag & 0x10) == 0)
        return TriggerType::Action;

    if ((flag & 8) == 0)
        return TriggerType::Property;

    if ((flag & 4) == 0)
        return TriggerType::Always;

    return TriggerType::Action;
}
}  // namespace xlink2::ResourceUtil