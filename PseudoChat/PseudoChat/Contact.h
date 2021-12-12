#pragma once

#include "pch.h"
#include <string>
#include <utility>

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime

#include "Contact.g.h"

#pragma pop_macro("GetCurrentTime")

namespace winrt::PseudoChat::implementation {
    class Contact: public ContactT<Contact> {
    private:
        winrt::hstring m_nickname;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    public:
        Contact() : m_nickname() {}
        Contact(winrt::hstring const& nickname) : m_nickname(nickname) {}
        ~Contact() {}
        winrt::hstring Nickname() const;

        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
        void PropertyChanged(winrt::event_token const& token);
    };
}

namespace winrt::PseudoChat::factory_implementation {
    struct Contact : ContactT<Contact, implementation::Contact> {};
}

