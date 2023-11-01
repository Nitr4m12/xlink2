#include "xlink2/xlink2ResourceAccessor.h"

namespace xlink2 {
ResourceAccessor::~ResourceAccessor() = default;

const ResAssetCallTable* ResourceAccessor::searchCallTable(const char* name) const {
    if (mUserResource && mSystem->isCallEnabled()) {
        UserResourceParam* param;
        if (ResMode::Editor >= mUserResource->getResMode())
            param = mUserResource->getParams()[(s32)mUserResource->getResMode()];
        else
            param = mUserResource->getParams()[0];

        if (param && param->isSetup)
            return mUserResource->searchAssetCallTableByName(name);
    }

    return nullptr;
}

const ResAssetCallTable* ResourceAccessor::searchCallTable(Locator* locator, const char* name) const {
    if (mUserResource && mSystem->isCallEnabled()) {
        UserResourceParam* param;
        if (ResMode::Editor >= mUserResource->getResMode())
            param = mUserResource->getParams()[(s32)mUserResource->getResMode()];
        else
            param = mUserResource->getParams()[0];

        if (param && param->isSetup)
            return mUserResource->searchAssetCallTableByName(locator, name);
    }

    // what does this mean??
    return (ResAssetCallTable*)mUserResource;
}

const ResAssetCallTable* ResourceAccessor::getCallTable(u32 idx) const {
    if (mUserResource && mSystem->isCallEnabled()) {
        UserResourceParam* param;
        if (ResMode::Editor >= mUserResource->getResMode())
            param = mUserResource->getParams()[(s32)mUserResource->getResMode()];
        else
            param = mUserResource->getParams()[0];

        if (param && param->isSetup) {
            if (idx < mUserHeader->numCallTable)
                return mUserResource->getAssetCallTableItem(idx);

            setError_("getCallTable: idx(%d) >= numCallTable(%d)", idx, mUserHeader->numCallTable);
        }

    }

    return nullptr;
}
}  // namespace xlink2