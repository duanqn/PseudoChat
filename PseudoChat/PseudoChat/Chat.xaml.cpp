#include "pch.h"
#include "Chat.xaml.h"
#if __has_include("Chat.g.cpp")
#include "Chat.g.cpp"
#endif

#include "Utils.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PseudoChat::implementation
{
    Chat::Chat(): m_manager(), m_resourceManager()
    {
        InitializeComponent();
    }

    void Chat::Send_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&) {
        auto prevMsg = PrevMessageBox().Text();
        auto currentMsg = processNewMsg(NewMessageBox().Text());
        auto&& context = m_resourceManager.CreateResourceContext();
        // context.QualifierValues().Insert(L"Language", L"zh-Hans")
        auto&& resourceMap = m_resourceManager.MainResourceMap();
        auto&& resource = resourceMap.GetValue(L"StringTable/SelfSentMsgHeader", context);
        winrt::hstring header = winrt::hstring(L"\n") + resource.ValueAsString() + winrt::hstring(L"\n");
        PrevMessageBox().Text(prevMsg + header + currentMsg);
        NewMessageBox().Text(L"");
    }

    PseudoChat::ContactManager Chat::Manager() const {
        return m_manager;
    }
}
