#pragma once

#include "Chat.g.h"

namespace winrt::PseudoChat::implementation
{
    struct Chat : ChatT<Chat>
    {
        Chat();

        void Send_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        PseudoChat::ContactManager Manager() const;

        protected:
        winrt::PseudoChat::ContactManager m_manager;
        winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager m_resourceManager;
    };
}

namespace winrt::PseudoChat::factory_implementation
{
    struct Chat : ChatT<Chat, implementation::Chat>
    {
    };
}
