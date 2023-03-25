#pragma once

#include <memory>
#include <concepts>

namespace pacman {
    template<std::semiregular T>
    requires std::is_scalar_v<T>
    /**
     * Wrapper for a shared_ptr
     * @tparam T type to wrap
     */
    class shared_value
    {
        std::shared_ptr<T> m_sharedValue;

    public:
        /**
         * @brief Constructs a new shared_value object with the default value of T.
         * @param value The default value of T to use.
         */
        [[nodiscard]] explicit shared_value(T value = T{})
                : m_sharedValue{std::make_shared<T>(value)}
        {}

        [[nodiscard]] inline T value() const noexcept
        { return *m_sharedValue; }

        [[nodiscard]] inline T &value() noexcept
        { return *m_sharedValue; }

        [[nodiscard]] inline T operator*() const noexcept
        { return value(); }

        [[nodiscard]] inline T &operator*() noexcept
        { return value(); }

        operator T() const noexcept
        { return value(); }

        operator T &() noexcept
        { return value(); }

        inline shared_value<T> &operator=(T newValue) noexcept
        {
            value() = newValue;
            return *this;
        }

        [[nodiscard]] inline T operator+(T v) const noexcept
        { return value() + v; }

        inline T &operator+=(T newValue) noexcept
        {
            value() += newValue;
            return value();
        }

        [[nodiscard]] inline T operator-(T v) const noexcept
        { return value() - v; }

        inline T &operator-=(T newValue) noexcept
        {
            value() -= newValue;
            return value();
        }

        inline T &operator++() noexcept
        {
            value() += 1;
            return value();
        }

        inline T &operator--() noexcept
        {
            value() -= 1;
            return value();
        }

        inline std::weak_ordering operator<=>(T rhs) const noexcept
        {
            return value() <=> rhs;
        }
    };
}