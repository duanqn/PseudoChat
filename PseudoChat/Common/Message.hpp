#include <cstdint>
#include <limits>
#include <istream>
#include <ostream>
#include <string>
#include <type_traits>

#include "Exception.h"

#pragma push_macro("max")
#undef max

namespace PseudoChat{
    template<typename T>
    concept simple_type = std::is_integral_v<T>;
    
    template<typename T>
    concept single_byte_type = std::is_integral_v<T> && sizeof(T) == 1;

    template<typename T>
    concept multi_byte_type = std::is_integral_v<T> && sizeof(T) > 1;

    template<typename T>
    class MessageField;

    template<simple_type T>
    class MessageField<T> {
    public:
        using type = T;

    private:
        type m_data;

    public:
        MessageField(): m_data(static_cast<type>(0)) {}
        ~MessageField() = default;

        const type& get() const {
            return m_data;
        }

        std::enable_if_t<std::is_copy_assignable_v<T>, T&> set(const T& data) {
            m_data = data;
            return m_data;
        }

        std::enable_if_t<std::is_move_assignable_v<T>, T&> set(T&& data) {
            m_data = std::move(data);
            return m_data;
        }

        size_t length() const {
            return sizeof(type);
        }
    };

    template<typename C>
    class MessageField<std::basic_string<C>> {
    public:
        using type = std::basic_string<C>;

    private:
        type m_data;

    public:
        MessageField(): m_data() {}
        ~MessageField() = default;

        const type& get() const {
            return m_data;
        }

        std::enable_if_t<std::is_copy_assignable_v<type>, type&> set(const type& data) {
            m_data = data;
            return m_data;
        }

        std::enable_if_t<std::is_move_assignable_v<type>, type&> set(type&& data) {
            m_data = std::move(data);
            return m_data;
        }

        size_t length() const {
            return m_data.size();
        }
    };
}   // namespace PseudoChat

/*
template<typename T>
std::ostream& operator<< (std::ostream& os, const PseudoChat::MessageField<T>& obj);
*/

template<::PseudoChat::simple_type T>
std::ostream& operator<< (std::ostream& os, const ::PseudoChat::MessageField<T>& obj) {
    char *mem = new char[obj.length()];
    using data_type = decltype(obj)::type;
    data_type* ptr = reinterpret_cast<data_type*>(mem);
    *ptr = obj.get();
    // TODO: Convert byte order here:
    switch(obj.length()){
        default:
            ;
    };

    for(size_t i = 0; i < obj.length(); ++i) {
        os.put(mem[i]);
    }

    delete[] mem;
    return os;
}

template<typename C>
std::ostream& operator<< (std::ostream& os, const ::PseudoChat::MessageField<std::basic_string<C>>& obj) {
    dynamic_assert(obj.length() < std::numeric_limits<uint32_t>::max(), "Failed: string length too long.");
    return os;
}

template<typename T>
std::istream& operator>> (std::istream& os, ::PseudoChat::MessageField<T>& obj);

#pragma pop_macro("max")
