#pragma once

#include "Navigation.g.h"

namespace winrt::PseudoChat::implementation
{
    struct Navigation : NavigationT<Navigation>
    {
        Navigation();

        void OnDisplayFrameNavigated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e);
        void CtrlF_Invoked(Microsoft::UI::Xaml::Input::KeyboardAccelerator const& sender, Microsoft::UI::Xaml::Input::KeyboardAcceleratorInvokedEventArgs const& args);
        void NavigationViewControl_ItemInvoked(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args);

        private:
        winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager m_resourceManager;
    };
}

namespace winrt::PseudoChat::factory_implementation
{
    struct Navigation : NavigationT<Navigation, implementation::Navigation>
    {
    };
}
