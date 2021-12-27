#pragma once

#include "Settings.g.h"

namespace winrt::PseudoChat::implementation
{
    struct Settings : SettingsT<Settings>
    {
        Settings();

        void OnRootFrameNavigated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e);
        void CtrlF_Invoked(Microsoft::UI::Xaml::Input::KeyboardAccelerator const& sender, Microsoft::UI::Xaml::Input::KeyboardAcceleratorInvokedEventArgs const& args);

        private:
        winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager m_resourceManager;
    };
}

namespace winrt::PseudoChat::factory_implementation
{
    struct Settings : SettingsT<Settings, implementation::Settings>
    {
    };
}
