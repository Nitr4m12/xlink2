#pragma once

namespace xlink2 {
class Error {
public:
    enum class Type {
        Info=0, // 情報　（じょうほう）
        Warning, // 警告　（けいこく）
        Error, // エラー
        Lethal // 致命的　（ちめいてき）
    };
};
}  // namespace xlink2