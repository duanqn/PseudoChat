#pragma once

#include "pch.h"

#include "Contact.h"

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime

#include "ContactManager.g.h"

#pragma pop_macro("GetCurrentTime")

#include <string>

namespace winrt::PseudoChat::implementation {
    class ContactManager : public ContactManagerT<ContactManager> {
    public:
        ContactManager();
        ~ContactManager() {}

        Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> Contacts();
    };
}

namespace winrt::PseudoChat::factory_implementation {
    struct ContactManager : ContactManagerT<ContactManager, implementation::ContactManager> {};
}

