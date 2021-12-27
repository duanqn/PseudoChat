#include "pch.h"
#include "ContactManager.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <vector>

#include "ContactManager.g.cpp"

using namespace winrt;

namespace winrt::PseudoChat::implementation {
    ContactManager::ContactManager() {}

    Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> ContactManager::Contacts()
    {
        std::vector<Windows::Foundation::IInspectable> contacts;
        contacts.push_back(winrt::make<Contact>(L"测试1"));
        contacts.push_back(winrt::make<Contact>(L"测试2"));
        auto res = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>(std::move(contacts));
        return res;
    }
}
