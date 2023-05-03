#pragma once

#include <memory>
#include <type_traits>

namespace pacman {
    template<typename T>
    /**
     * Wrapper for a shared_ptr
     * @tparam T type to wrap
     */
    class shared_value
    {
        static_assert(std::is_scalar_v<T>, "shared_value<T> requires T to be a scalar type.");

        std::shared_ptr<T> m_sharedValue;

    public:
        /**
         * @brief Constructs a new shared_value object with the default value of T.
         * @param value The default value of T to use.
         */
        explicit shared_value(T value = T{})
                : m_sharedValue{std::make_shared<T>(value)}
        {}

        [[nodiscard]] inline T value() const
        { return *m_sharedValue; }

        [[nodiscard]] inline T &value()
        { return *m_sharedValue; }

        [[nodiscard]] inline T operator*() const
        { return value(); }

        [[nodiscard]] inline T &operator*()
        { return value(); }

        operator T() const
        { return value(); }

        operator T &()
        { return value(); }

        inline shared_value<T> &operator=(T newValue)
        {
            value() = newValue;
            return *this;
        }

        [[nodiscard]] inline T operator+(T v) const
        { return value() + v; }

        inline T operator+=(T newValue)
        {
            value() += newValue;
            return value();
        }

        [[nodiscard]] inline T operator-(T v) const
        { return value() - v; }

        inline T operator-=(T newValue)
        {
            value() -= newValue;
            return value();
        }

        inline T operator++()
        {
            value() += 1;
            return value();
        }

        inline T operator--()
        {
            value() -= 1;
            return value();
        }

        inline bool operator<(const T &rhs) const {
            return value() < rhs;
        }

        inline bool operator>(const T &rhs) const {
            return rhs < value();
        }

        inline bool operator<=(const T &rhs) const {
            return rhs >= value();
        }

        inline bool operator>=(const T &rhs) const {
            return value() >= rhs;
        }

        inline bool operator==(const T &rhs) const {
            return value() == rhs;
        }

        inline bool operator!=(const T &rhs) const {
            return rhs != value();
        }

    };
}
