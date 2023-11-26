#include "xlink2/xlink2EditorBuffer.h"

namespace xlink2 {
void EditorBuffer::setupParamDefineTable(u8* param_define_bin, u32 param_define_size)
{
    memcpy(mParamDefineBuffer, param_define_bin, param_define_size);
    if (mParamDefineTable->isInitilized())
        mParamDefineTable->reset();
    mParamDefineTable->setup(mParamDefineBuffer, mSystem->getUserParamNum(),
                             mSystem->debugOperationParamOR().get258() & 1);
}
}  // namespace xlink2