#pragma once

#include "sprite-animation.h"
#include "utils/position.h"

namespace pacman {

    enum class BoardCaseType {
        PointPath,
        BasicPath,
        Bonus,
        Wall,
        GhostHome,
        GhostHomeDoor,
        DoorLeft,
        DoorRight,
        Nothing
    };

    class BoardCase {
        int m_x;
        int m_y;
        BoardCaseType m_type;
        uint8_t m_flags;
        std::optional<SpriteAnimation> m_animation;
    public:
        BoardCase() : m_x{0}, m_y{0}, m_flags{0}, m_type(BoardCaseType::PointPath) {}

        ~BoardCase() = default;

        BoardCase(int p_x, int p_y, BoardCaseType p_type,
                  uint8_t flags, const std::optional<SpriteAnimation> &p_animation)
                  : m_x{p_x}, m_y{p_y}, m_type{p_type}, m_flags{flags}, m_animation(p_animation) {}

        [[nodiscard]] constexpr int x() const noexcept { return m_x; }

        constexpr int &x() noexcept { return m_x; }

        [[nodiscard]] constexpr int y() const { return m_y; }

        constexpr int &y() noexcept { return m_y; }

        [[nodiscard]] constexpr uint8_t flags() const { return m_flags; }
        constexpr uint8_t &flags() { return m_flags; }

        [[nodiscard]] BoardCaseType type() const noexcept { return m_type; }

        BoardCaseType &type() noexcept { return m_type; }

        [[nodiscard]] std::optional<SpriteAnimation> const &animation() const noexcept { return m_animation; }

        std::optional<SpriteAnimation> &animation() noexcept { return m_animation; };

        [[nodiscard]] Position position() const noexcept { return {m_x, m_y}; }

        static inline bool isPracticable(BoardCase p_boardCase) noexcept {
            return isTypePracticable(p_boardCase.type());
        }

        static inline bool isTypePracticable(BoardCaseType p_boardCaseType) noexcept {
            return p_boardCaseType == BoardCaseType::PointPath
                   || p_boardCaseType == BoardCaseType::BasicPath
                   || p_boardCaseType == BoardCaseType::Bonus
                   || p_boardCaseType == BoardCaseType::DoorLeft
                   || p_boardCaseType == BoardCaseType::DoorRight
                   || p_boardCaseType == BoardCaseType::GhostHome;
        }

    };

    using DirectionBoardCasePair = std::pair<Direction, std::optional<BoardCase>>;

    [[nodiscard]] DirectionBoardCasePair
    getClosestBoardCase(Position p_target, std::span<const DirectionBoardCasePair> p_boardCases,
                        bool p_acceptHomeDoor = false) noexcept;


}