#include "pch.h"
#include "Settings.xaml.h"
#if __has_include("Settings.g.cpp")
#include "Settings.g.cpp"
#endif

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::UI::Xaml;
using Language = ::PseudoChat::Settings::Language;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PseudoChat::implementation
{
    Settings::Settings(): m_resourceManager(), m_settings(::PseudoChat::Singleton<::PseudoChat::Settings>::getInstance()), m_selectedLanguage(m_settings->data().language.get()), m_observerToken(0), m_LanguageToUIPosition()
    {
        InitializeComponent();

        ::PseudoChat::Settings& globalSettings = m_settings->data();
        m_observerToken = globalSettings.language.registerObserver([this](const std::string&, ::PseudoChat::Settings::Language, ::PseudoChat::Settings::Language current) {
            if (this->IsLoaded()) {
                localizePage(current);
            }
        });

        m_LanguageToUIPosition.insert(std::make_pair(Language::Default, 0));
        m_LanguageToUIPosition.insert(std::make_pair(Language::Chinese_CHS, 1));
        m_LanguageToUIPosition.insert(std::make_pair(Language::English_EN, 2));
    }

    Settings::~Settings() {
        ::PseudoChat::Settings& globalSettings = m_settings->data();
        globalSettings.language.unregisterObserver(m_observerToken);
    }

    void Settings::LanguageDropdown_Click(IInspectable const& sender, RoutedEventArgs const& e) {
        Controls::MenuFlyoutItem itemClicked = sender.as<Controls::MenuFlyoutItem>();

        auto&& dropdownList = LanguageDropdown().Flyout().as<Controls::MenuFlyout>().Items();

        for (uint32_t i = 0; i < dropdownList.Size(); ++i) {
            if (itemClicked == dropdownList.GetAt(i).as<Controls::MenuFlyoutItem>()) {
                m_selectedLanguage = m_LanguageToUIPosition.at(i);
            }
        }

        ::PseudoChat::Settings& globalSettings = m_settings->data();
        globalSettings.language.set(m_selectedLanguage);
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
        LanguageDropdown().Content(winrt::box_value(vec.GetAt(m_LanguageToUIPosition[m_selectedLanguage]).as<Controls::MenuFlyoutItem>().Text()));
    }

    void Settings::SettingsPage_Loaded(IInspectable const&, RoutedEventArgs const&)
    {
        localizePage(m_settings->data().language.get());
    }
}
