#include "pch.h"
#include "Settings.xaml.h"
#if __has_include("Settings.g.cpp")
#include "Settings.g.cpp"
#endif

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PseudoChat::implementation
{
    Settings::Settings(): m_resourceManager(), m_settings(::PseudoChat::Singleton<::PseudoChat::Settings>::getInstance()), m_selectedLanguageItem(0)
    {
        InitializeComponent();

        ::PseudoChat::Settings& globalSettings = m_settings->data();
        globalSettings.language.registerObserver([this](const std::string&, ::PseudoChat::Settings::Language, ::PseudoChat::Settings::Language current) {
            if (this->IsLoaded()) {
                localizePage(current);
            }
        });
    }

    void Settings::LanguageDropdown_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        Controls::MenuFlyoutItem itemClicked = sender.as<Controls::MenuFlyoutItem>();

        auto&& dropdownList = LanguageDropdown().Flyout().as<Controls::MenuFlyout>().Items();

        for (uint32_t i = 0; i < dropdownList.Size(); ++i) {
            if (itemClicked == dropdownList.GetAt(i).as<Controls::MenuFlyoutItem>()) {
                m_selectedLanguageItem = i;
            }
        }

        ::PseudoChat::Settings& globalSettings = m_settings->data();
        switch (m_selectedLanguageItem)
        {
        case 0:
            globalSettings.language.set(::PseudoChat::Settings::Language::Default);
            break;
        case 1:
            globalSettings.language.set(::PseudoChat::Settings::Language::Chinese_CHS);
            break;
        case 2:
            globalSettings.language.set(::PseudoChat::Settings::Language::English_EN);
            break;
        default:
            WINRT_ASSERT(false);
        }
    }

    void Settings::localizePage(::PseudoChat::Settings::Language language) {
        auto context = m_resourceManager.CreateResourceContext();
        winrt::hstring localeString = winrt::hstring(::PseudoChat::g_localeStrings[static_cast<int>(language)]);
        if (language != ::PseudoChat::Settings::Language::Default) {
            context.QualifierValues().Insert(L"Language", localeString);
        }

        auto&& resourceMap = m_resourceManager.MainResourceMap();

        auto&& text = resourceMap.GetValue(L"StringTable/LanguageDefault", context);
        LanguageDropdown_Default().Text(text.ValueAsString());

        text = resourceMap.GetValue(L"StringTable/LanguageChinese", context);
        LanguageDropdown_CHS().Text(text.ValueAsString());

        text = resourceMap.GetValue(L"StringTable/SettingsLanguageText", context);
        LanguageDropdown_Text().Text(text.ValueAsString());
        
        text = resourceMap.GetValue(L"StringTable/SettingsModeText", context);
        Mode_Text().Text(text.ValueAsString());

        text = resourceMap.GetValue(L"StringTable/ModeNormal", context);
        ModeNormal().Content(winrt::box_value(text.ValueAsString()));

        text = resourceMap.GetValue(L"StringTable/ModeQingLang", context);
        ModeQingLang().Content(winrt::box_value(text.ValueAsString()));

        // Keep at the end
        updateDropdownSelection();
    }

    void Settings::updateDropdownSelection() {
        auto&& vec = LanguageDropdown().Flyout().as<Controls::MenuFlyout>().Items();
        LanguageDropdown().Content(winrt::box_value(vec.GetAt(m_selectedLanguageItem).as<Controls::MenuFlyoutItem>().Text()));
    }

    void Settings::SettingsPage_Loaded(IInspectable const&, RoutedEventArgs const&)
    {
        localizePage(m_settings->data().language.get());
    }
}
