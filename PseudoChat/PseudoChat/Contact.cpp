#include "pch.h"
#include "Contact.h"
#include <string>

#include "Contact.g.cpp"

namespace winrt::PseudoChat::implementation {
    winrt::hstring Contact::Nickname() const {
        return m_nickname;
    }

    winrt::event_token Contact::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value) {
        return m_propertyChanged.add(value);
    }

    void Contact::PropertyChanged(winrt::event_token const& token) {
        m_propertyChanged.remove(token);
    }
}
