#pragma once

#include <memory>

namespace pacman {
    template<std::integral T>
    class shared_value {
        std::shared_ptr<T> m_sharedValue;

    public:
        explicit shared_value(T value = T(0))
                : m_sharedValue{std::make_shared<T>(value)} {
        }

        [[nodiscard]] inline T value() const noexcept { return *m_sharedValue; }

        [[nodiscard]] inline T &value() noexcept { return *m_sharedValue; }

        explicit operator T() const noexcept { return value(); }

        explicit operator T &() noexcept { return value(); }

        T& operator =(T newValue) noexcept { value() = newValue; return value(); }

        T& operator +(T newValue) noexcept { value() += newValue; return value(); }

        T& operator -(T newValue) noexcept { value() -= newValue; return value(); }

        bool operator<=>(const T &rhs) const noexcept {
            return value() <=> rhs;
        }

    };
}