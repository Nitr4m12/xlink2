#include "xlink2/xlink2ResourceAccessor.h"

namespace xlink2 {
ResourceAccessor::~ResourceAccessor() = default;

bool ResourceAccessor::isContainer(ResAssetCallTable const& res_asset_call_table) const {
    return res_asset_call_table.flag & 1;
}
}  // namespace xlink2