#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Security::Cryptography::Core;
using namespace Microsoft::UI::Xaml::Navigation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PseudoChat::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        auto provider = AsymmetricKeyAlgorithmProvider::OpenAlgorithm(AsymmetricAlgorithmNames::RsaSignPkcs1Sha256());
        auto keyPair = provider.CreateKeyPair(2048);
        keyPair.Export(CryptographicPrivateKeyBlobType::BCryptPrivateKey);

        MainFrame().Navigate(winrt::xaml_typename<Settings>());
    }

    winrt::hstring MainWindow::WindowTitle()
    {
        return Windows::ApplicationModel::Package::Current().DisplayName();
    }

    void MainWindow::MainFrame_Navigated(IInspectable const&, NavigationEventArgs const&)
    {
    }
}
