#pragma once

#include <mutex>

namespace PseudoChat {
    template<typename T> requires std::is_default_constructible_v<T>
    class Singleton final: public T {
        private:
        static std::once_flag m_singletonFlag;
        static Singleton<T>* m_instance;

        Singleton(): T() {}
        static void init() {
            m_instance = new Singleton<T>;
        }

        public:
        T& data() {
            return *(static_cast<T*>(this));
        }

        const T& data() const {
            return *(static_cast<const T*>(this));
        }

        static Singleton* getInstance() {
            std::call_once(Singleton<T>::m_singletonFlag, Singleton::init);
            return m_instance;
        }

        Singleton(const Singleton& other) = delete;
        Singleton(Singleton&& other) = delete;
        Singleton& operator = (const Singleton& other) = delete;
        Singleton& operator = (Singleton&& other) = delete;
    };

    template<typename T> requires std::is_default_constructible_v<T>
    std::once_flag Singleton<T>::m_singletonFlag = {};

    template<typename T> requires std::is_default_constructible_v<T>
    Singleton<T>* Singleton<T>::m_instance = nullptr;
}   // namespace PseudoChat
