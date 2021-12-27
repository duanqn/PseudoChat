#include "pch.h"
#include "Settings.xaml.h"
#if __has_include("Settings.g.cpp")
#include "Settings.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PseudoChat::implementation
{
    Settings::Settings(): m_resourceManager()
    {
        InitializeComponent();

        auto&& searchBox = controlsSearchBox();

        auto&& context = m_resourceManager.CreateResourceContext();
        // context.QualifierValues().Insert(L"Language", L"zh-Hans")
        auto&& resourceMap = m_resourceManager.MainResourceMap();
        auto&& resource = resourceMap.GetValue(L"StringTable/SearchPlaceholder", context);
        
        searchBox.PlaceholderText(resource.ValueAsString());
    }

    void Settings::OnRootFrameNavigated(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
    }
    void Settings::CtrlF_Invoked(Microsoft::UI::Xaml::Input::KeyboardAccelerator const&, Microsoft::UI::Xaml::Input::KeyboardAcceleratorInvokedEventArgs const&)
    {
    }
}
