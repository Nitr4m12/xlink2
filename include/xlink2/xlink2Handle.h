#pragma once

namespace xlink2 {
class Handle {
public:
    void* get0() { return _0; }
    int get8() { return _8; }

private:
    void* _0 = nullptr;
    int _8 = 0;
};
}  // namespace xlink2