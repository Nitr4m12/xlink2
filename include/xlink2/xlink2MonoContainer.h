#pragma once

#include "xlink2/xlink2ContainerBase.h"
#include "xlink2/xlink2Event.h"
#include "xlink2/xlink2ResAssetCallTable.h"

namespace xlink2 {
class MonoContainer : ContainerBase {
    ~MonoContainer() override;

public:
    u32 calc() override;
    void* killOneTimeEvent() override;
    void kill() override;

    void fade(int) override;
    void destroy() override;
    void fadeBySystem() override;

    void initialize(Event*, const ResAssetCallTable&) override;

    bool start() override;

private:
    f32 _1;
    f32 _2;
};
}  // namespace xlink2