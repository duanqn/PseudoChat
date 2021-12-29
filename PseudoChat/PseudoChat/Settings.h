#pragma once

#include "Observable.hpp"

#include <array>
#include <atomic>
#include <string>

namespace PseudoChat {
    class Settings {
    private:
    public:
        enum class Language : int {
            Default,
            Chinese_CHS,
            English_EN,
            SIZE
        };

        Observable<Language> language;

        Settings();
        virtual ~Settings() {}
    };

    constexpr std::array<std::wstring_view, static_cast<size_t>(Settings::Language::SIZE)> g_localeStrings = {
        L"",
        L"zh-Hans",
        L"en-US"
    };
}   // namespace PseudoChat
