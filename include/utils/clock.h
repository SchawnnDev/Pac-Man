#pragma once

#include <chrono>

namespace pacman {

    class Clock final
    {
        using source_clock = std::chrono::steady_clock;
        using time_point = source_clock::time_point;
        using duration = source_clock::duration;

        const time_point m_start;

        uint64_t m_frame_count{};
        duration m_last_delta{};
        time_point m_frame_start{};

    public:
        Clock() noexcept
                : m_start{ source_clock::now() }
                , m_frame_start{ m_start }
        { }

        [[nodiscard]] inline uint64_t frame_count() const noexcept { return m_frame_count; }
        [[nodiscard]] inline uint64_t since_start() const noexcept { return std::chrono::duration_cast<std::chrono::milliseconds>(source_clock::now() - m_start).count(); }
        [[nodiscard]] inline double last_delta() const noexcept { return std::chrono::duration<double, std::milli>{m_last_delta}.count(); }

        /**
         * Begin frame
         */
        void begin_frame() noexcept
        {
            m_frame_start = source_clock::now();
        }

        /**
         * End frame
         */
        void end_frame() noexcept
        {
            const auto now = source_clock::now();
            m_last_delta = now - m_frame_start;

            m_frame_count++;
        }
    };
}