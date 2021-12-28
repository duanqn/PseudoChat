#include "pch.h"
#include "Navigation.xaml.h"
#if __has_include("Navigation.g.cpp")
#include "Navigation.g.cpp"
#endif

#include "Chat.xaml.h"
#include "Settings.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PseudoChat::implementation
{
    Navigation::Navigation(): m_resourceManager(), m_settings(::PseudoChat::Singleton<::PseudoChat::Settings>::getInstance()) {
        InitializeComponent();

        ::PseudoChat::Settings& globalSettings = m_settings->data();
        globalSettings.language.registerObserver([this](const std::string&, ::PseudoChat::Settings::Language, ::PseudoChat::Settings::Language) {
            if (this->IsLoaded()) {
                localizePage();
            }
        });

        // globalSettings.language.set(::PseudoChat::Settings::Language::Default);
    }

    void Navigation::OnDisplayFrameNavigated(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
    }
    void Navigation::CtrlF_Invoked(Microsoft::UI::Xaml::Input::KeyboardAccelerator const&, Microsoft::UI::Xaml::Input::KeyboardAcceleratorInvokedEventArgs const&)
    {
    }

    void Navigation::localizePage() {
        auto&& context = m_resourceManager.CreateResourceContext();
        // context.QualifierValues().Insert(L"Language", L"zh-Hans")
        auto&& resourceMap = m_resourceManager.MainResourceMap();
        auto&& resource = resourceMap.GetValue(L"StringTable/SearchPlaceholder", context);
        
        auto&& searchBox = controlsSearchBox();
        searchBox.PlaceholderText(resource.ValueAsString());

        auto&& navChatItem = navChat();
        resource = resourceMap.GetValue(L"StringTable/navChatText", context);
        navChatItem.Content(winrt::box_value(resource.ValueAsString()));
    }

    void Navigation::NavigationViewControl_ItemInvoked(NavigationView const& sender, NavigationViewItemInvokedEventArgs const& args)
    {
        WINRT_ASSERT(sender == NavigationViewControl());

        if (args.InvokedItemContainer().IsSelected()) {
            // Selecting an item that is already selected.
            return;
        }

        auto&& frame = DisplayFrame();

        if (args.IsSettingsInvoked()) {
            frame.Navigate(winrt::xaml_typename<winrt::PseudoChat::Settings>());
            return;
        }

        // Figure out which item is invoked.
        auto&& invokedItem = args.InvokedItem();
        winrt::Windows::Foundation::PropertyType propertyType = invokedItem.as<winrt::Windows::Foundation::IPropertyValue>().Type();
        // `invokedItem` is the boxed NavigationViewItem.Content
        // Here we assert that it is a winrt::hstring
        WINRT_ASSERT(propertyType == winrt::Windows::Foundation::PropertyType::String);

        // Assertion OK; Unbox it as a winrt::hstring
        auto invokedString = winrt::unbox_value<winrt::hstring>(invokedItem);

        winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem invokedViewItem = args.InvokedItemContainer().as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();

        if (invokedViewItem == navChat()) {
            frame.Navigate(winrt::xaml_typename<winrt::PseudoChat::Chat>());
        }
    }

    void Navigation::Navigation_Loaded(IInspectable const&, RoutedEventArgs const&)
    {
        localizePage();
    }
}
