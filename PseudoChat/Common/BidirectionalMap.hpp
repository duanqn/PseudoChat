#pragma once

#include <map>
#include <type_traits>
#include <utility>

namespace PseudoChat {
    template<typename T1, typename T2>
    class BidirectionalMap final {
    private:
        std::map<T1, T2> m_forward;
        std::map<T2, T1> m_backward;

    public:
        BidirectionalMap() : m_forward(), m_backward() {}
        ~BidirectionalMap() = default;

        std::enable_if_t<!std::is_same_v<T1, T2>, const T2&> at(const T1& lookup) const {
            return m_forward.at(lookup);
        }

        std::enable_if_t<!std::is_same_v<T1, T2>, const T1&> at(const T2& lookup) const {
            return m_backward.at(lookup);
        }

        const T2& operator [] (const T1& lookup) const {
            return at(lookup);
        }

        const T1& operator [] (const T2& lookup) const {
            return at(lookup);
        }

        const T2& forward_at(const T1& lookup) const {
            return m_forward.at(lookup);
        }

        const T1& backward_at(const T2& lookup) const {
            return m_backward.at(lookup);
        }

        void insert(std::pair<T1, T2>&& entry) {
            m_backward.insert(std::make_pair(entry.second, entry.first));
            m_forward.insert(std::move(entry));
        }

        void clear() {
            m_forward.clear();
            m_backward.clear();
        }
    };
}   // namespace PseudoChat
