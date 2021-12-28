#pragma once

#include "Navigation.g.h"
#include "Settings.h"
#include "Singleton.hpp"

namespace winrt::PseudoChat::implementation
{
    struct Navigation : NavigationT<Navigation>
    {
        Navigation();

        void OnDisplayFrameNavigated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e);
        void CtrlF_Invoked(Microsoft::UI::Xaml::Input::KeyboardAccelerator const& sender, Microsoft::UI::Xaml::Input::KeyboardAcceleratorInvokedEventArgs const& args);
        void NavigationViewControl_ItemInvoked(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args);
        void Navigation_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        private:
        winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager m_resourceManager;
        ::PseudoChat::Singleton<::PseudoChat::Settings>* m_settings;

        void localizePage();
    };
}

namespace winrt::PseudoChat::factory_implementation
{
    struct Navigation : NavigationT<Navigation, implementation::Navigation>
    {
    };
}
