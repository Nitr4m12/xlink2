#pragma once

#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class MonoContainer : public ContainerBase {
    ~MonoContainer() override;

public:
    u32 calc() override;
    bool killOneTimeEvent() override;
    void kill() override;

    void fade(int) override;
    void destroy() override;
    void fadeBySystem() override;

    bool initialize(Event*, const ResAssetCallTable&) override;

    bool start() override;

private:
    f32 _1;
    f32 _2;
};
}  // namespace xlink2