#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "Contact.h"
#include "Utils.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Security::Cryptography::Core;
using namespace Windows::UI::ViewManagement;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PseudoChat::implementation
{
    MainWindow::MainWindow(): m_manager(winrt::make<ContactManager>())
    {
        InitializeComponent();
        auto provider = AsymmetricKeyAlgorithmProvider::OpenAlgorithm(AsymmetricAlgorithmNames::RsaSignPkcs1Sha256());
        auto keyPair = provider.CreateKeyPair(2048);
        keyPair.Export(CryptographicPrivateKeyBlobType::BCryptPrivateKey);

        PrevMessageBox().IsReadOnly(true);
        auto view = ApplicationView::GetForCurrentView();
        view.SetPreferredMinSize({0, 0});
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::Send_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&) {
        auto prevMsg = PrevMessageBox().Text();
        auto currentMsg = processNewMsg(NewMessageBox().Text());
        winrt::hstring header = L"\nYou:\n";
        PrevMessageBox().Text(prevMsg + header + currentMsg);
        NewMessageBox().Text(L"");
    }

    PseudoChat::ContactManager MainWindow::Manager() const {
        return m_manager;
    }
}
