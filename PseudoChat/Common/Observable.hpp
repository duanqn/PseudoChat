#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <type_traits>
#include <utility>
#include <vector>

#include "Concepts.h"
#include "Exception.h"

namespace PseudoChat {
    template<HasEquality T> requires std::is_copy_assignable_v<T>
    class Observable final {
    public:
        using Token = uint32_t;
        using Callback = std::function<void(const std::string&, const T&, const T&)>;

    private:
        std::string m_identifier;
        T m_data;
        std::unordered_map<Token, std::unique_ptr<Callback>> m_observers;
        Token m_nextToken;
        std::mutex m_mutex;

    public:
        template<typename U> requires std::is_constructible_v<T, U&&>
        Observable(const std::string& id, U&& init) : m_identifier(id), m_data(std::forward<U>(init)), m_observers(), m_nextToken(0), m_mutex() {}

        ~Observable() {}

        const T& get() const {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_data;
        }

        void set(const T& other) {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_data == other) {
                return;
            }

            T old = m_data;
            m_data = other;
            for (auto it = m_observers.begin(); it != m_observers.end(); ++it) {
                it->second->operator ()(m_identifier, old, m_data);
            }
        }

        Token registerObserver(const Callback& f) {
            std::lock_guard<std::mutex> lock(m_mutex);
            auto res = m_observers.insert(std::make_pair(m_nextToken, std::make_unique<Callback>(f)));
            if (!res.second) {
                // Insertion did not happen.
                throw Exception("registerObserver Failed: Token already assigned.");
            }

            Token assignedToken = m_nextToken;
            ++m_nextToken;
            return assignedToken;
        }

        void unregisterObserver(const Token& token) {
            std::lock_guard<std::mutex> lock(m_mutex);
            auto it = m_observers.find(token);
            if (it != m_observers.end()) {
                m_observers.erase(it);
            }
        }
    };
}
