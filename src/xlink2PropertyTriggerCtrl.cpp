#include "xlink2/xlink2PropertyTriggerCtrl.h"

namespace xlink2 {
void PropertyTriggerCtrl::reset() {
    _1 = 0;
    _2 = 1;
    TriggerCtrl::resetIsOnceCheck_();
}
}