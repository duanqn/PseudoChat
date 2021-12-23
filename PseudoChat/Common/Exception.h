#pragma once

#include <string>
#include <concepts>
#include <functional>
#include <type_traits>

namespace PseudoChat {
    namespace Concept {
        template<typename T>
        concept acceptable_exception_content = std::constructible_from<std::string, T&&>;
    }

    class Exception {
        private:
        std::string m_msg;
        public:
        Exception() = default;
        template<Concept::acceptable_exception_content T>
        Exception(T&& arg): m_msg(std::forward<T>(arg)) {}
        virtual ~Exception() = default;
        const char* what();
    };

    template<Concept::acceptable_exception_content T>
    void dynamic_assert(bool condition, T&& arg) {
        if(!condition) {
            throw Exception(std::forward<T>(arg));
        }
    }
}   // namespace PseudoChat
