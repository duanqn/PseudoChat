#pragma once

#include "Settings.g.h"

namespace winrt::PseudoChat::implementation
{
    struct Settings : SettingsT<Settings>
    {
        Settings();
    };
}

namespace winrt::PseudoChat::factory_implementation
{
    struct Settings : SettingsT<Settings, implementation::Settings>
    {
    };
}
