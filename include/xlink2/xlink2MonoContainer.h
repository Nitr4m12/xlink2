#pragma once

#include "xlink2/xlink2ContainerBase.h"

namespace xlink2 {
class MonoContainer : public ContainerBase {
public:
    ~MonoContainer() override;
    
    CalcResult calc() override;

    bool killOneTimeEvent() override;
    void kill() override;

    void fade(s32) override;
    void destroy() override;
    void fadeBySystem() override;

    bool initialize(Event*, const ResAssetCallTable&) override;

    bool start() override;

private:
    f32 _1;
    f32 _2;
};
}  // namespace xlink2