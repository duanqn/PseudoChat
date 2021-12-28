#pragma once

#include <atomic>

#include "Observable.hpp"

namespace PseudoChat {
    class Settings {
    private:
    public:
        enum class Language : int {
            Default,
            Chinese_CHS,
            English_EN
        };

        Observable<Language> language;

        Settings();
        virtual ~Settings() {}
    };
}   // namespace PseudoChat
