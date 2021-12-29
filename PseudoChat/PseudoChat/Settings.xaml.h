#pragma once

#include "Settings.g.h"

#include "Singleton.hpp"
#include "Settings.h"

#include <cstdint>

namespace winrt::PseudoChat::implementation
{
    struct Settings : SettingsT<Settings>
    {
        Settings();
        void LanguageDropdown_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SettingsPage_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        private:
        winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager m_resourceManager;
        ::PseudoChat::Singleton<::PseudoChat::Settings>* m_settings;
        uint32_t m_selectedLanguageItem;

        void localizePage(::PseudoChat::Settings::Language language);
        void updateDropdownSelection();
    };
}

namespace winrt::PseudoChat::factory_implementation
{
    struct Settings : SettingsT<Settings, implementation::Settings>
    {
    };
}
