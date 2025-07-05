#pragma once

namespace xlink2 {
class ToolConnectionContext {
public:
    void addLabel(const char*);

private:
    char* mLabel;
};
}  // namespace xlink2