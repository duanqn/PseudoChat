#pragma once

#include "Chat.g.h"

#include "Settings.h"
#include "Singleton.hpp"

namespace winrt::PseudoChat::implementation
{
    struct Chat : ChatT<Chat>
    {
        Chat();

        void Send_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        PseudoChat::ContactManager Manager() const;
        void ChatPage_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        private:
        winrt::PseudoChat::ContactManager m_manager;
        winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager m_resourceManager;
        ::PseudoChat::Singleton<::PseudoChat::Settings>* m_settings;

        void localizePage(::PseudoChat::Settings::Language language);
    };
}

namespace winrt::PseudoChat::factory_implementation
{
    struct Chat : ChatT<Chat, implementation::Chat>
    {
    };
}
