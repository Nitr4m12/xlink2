#include <basis/seadTypes.h>

namespace xlink2 {
struct PropertyValueType {
    union {
        f32 valueFloat;
        s32 valueInt;
    };
};
}