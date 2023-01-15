#include <xlink2/xlink2UserResource.h>

namespace xlink2 {
UserResource::~UserResource() = default;
UserResource::UserResource(User* user) {
    mUser = user;
    mResMode = (ResMode)0;
    mUserResourceParam = nullptr;
    _1 = nullptr;
}

void UserResource::freeResourceParam_(UserResourceParam* param) {
    if (param->nameTable != nullptr) {
        delete[] param->nameTable;
        param->nameTable = nullptr;
        param->nameTableNum = 0;
    }

    if (param->_1 != nullptr) {
        delete[] param->_1;
        param->_1 = nullptr;
        param->_0 = 0;
    }

    if (param->_3 != nullptr) {
        delete[] param->_3;
        param->_3 = nullptr;
        param->_2 = 0;
    }
}
}  // namespace xlink2