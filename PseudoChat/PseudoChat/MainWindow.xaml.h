#pragma once

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime

#include "MainWindow.g.h"

#pragma pop_macro("GetCurrentTime")

#include "ContactManager.h"
#include "Settings.h"
#include "Singleton.hpp"

namespace winrt::PseudoChat::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void MainFrame_Navigated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e);
        winrt::hstring WindowTitle();

        private:
        ::PseudoChat::Singleton<::PseudoChat::Settings>* m_settings;
    };
}

namespace winrt::PseudoChat::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
