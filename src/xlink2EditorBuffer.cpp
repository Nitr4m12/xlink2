#include "xlink2/xlink2EditorBuffer.h"

namespace xlink2 {
EditorBuffer::~EditorBuffer() = default;

EditorBuffer::EditorBuffer(System* system, sead::Heap* heap)
    : mSystem(system), mHeap(heap)
{
    auto* param_define_table = new (heap, 8) ParamDefineTable;
    param_define_table->reset();
    mParamDefineTable = param_define_table;
    mParamDefineBuffer = new (heap, 8) u8[0x800];

    mParams.initOffset(0xf0);
}

u8* EditorBuffer::allocReceiveBuffer(u32 buffer_size)
{
    delete[] mReceiveBuffer;

    if (mHeap->getFreeSize() < buffer_size)
        return nullptr;

    mReceiveBuffer = new (mHeap, 8) u8[buffer_size];
    mReceiveBufferSize = buffer_size;
    return mReceiveBuffer;
}

void EditorBuffer::setupParamDefineTable(u8* param_define_bin, u32 param_define_size)
{
    memcpy(mParamDefineBuffer, param_define_bin, param_define_size);
    if (mParamDefineTable->isInitilized())
        mParamDefineTable->reset();
    mParamDefineTable->setup(mParamDefineBuffer, mSystem->getUserParamNum(),
                             mSystem->debugOperationParamOR().get258Check());
}
}  // namespace xlink2