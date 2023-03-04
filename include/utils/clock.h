#pragma once

#include <chrono>

namespace pacman {

    class Clock final {
        using source_clock = std::chrono::steady_clock;
        using time_point = source_clock::time_point;
        using duration = source_clock::duration;

        const time_point m_start;

        uint64_t m_frame_count{};
        time_point m_last_tick{};
        duration m_last_delta{};

        static constexpr double to_seconds(duration du) noexcept {
            return std::chrono::duration_cast<std::chrono::microseconds>(
                    du).count() *
                   static_cast<double>(std::chrono::microseconds::period::den);
        }

    public:
        Clock() noexcept
                : m_start{source_clock::now()} {}

        [[nodiscard]] inline uint64_t frame_count() const noexcept { return m_frame_count; }
        [[nodiscard]] inline double since_start() const noexcept { return to_seconds(source_clock::now() - m_start); }
        [[nodiscard]] inline double last_delta() const noexcept { return to_seconds(m_last_delta); }

        void tick() noexcept {
            auto now = source_clock::now();
            m_last_delta = now - m_last_tick;
            m_last_tick = now;

            m_frame_count++;
        }
    };
}