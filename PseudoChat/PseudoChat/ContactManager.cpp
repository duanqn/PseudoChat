#include "pch.h"
#include "ContactManager.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <vector>

#include "ContactManager.g.cpp"

using namespace winrt;

namespace winrt::PseudoChat::implementation {
	ContactManager::ContactManager(): m_contacts() {
		m_contacts.push_back(winrt::make<Contact>(L"测试1"));
		m_contacts.push_back(winrt::make<Contact>(L"测试2"));
	}

	Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> ContactManager::Contacts()
	{
		auto res = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>(std::move(m_contacts));
		return res;
	}
}
