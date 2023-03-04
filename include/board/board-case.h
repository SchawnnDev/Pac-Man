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
        GhostHomeDoorLeft,
        GhostHomeDoorRight,
        GhostHomeDoor,
        DoorLeft,
        DoorRight,
        GhostUpForbidden,
        GhostTunnelSlowDown,
        Nothing
    };

    class BoardCase {
        int m_x;
        int m_y;
        BoardCaseType m_type;
        std::optional<SpriteAnimation> m_animation;
    public:
        BoardCase() : m_x(0), m_y(0), m_type(BoardCaseType::PointPath) {}

        ~BoardCase() = default;

        BoardCase(const int &p_x, const int &p_y, const BoardCaseType &p_type,
                  const std::optional<SpriteAnimation> &p_animation) : m_x(p_x), m_y(p_y), m_type(p_type),
                                                                       m_animation(p_animation) {}

        [[nodiscard]] constexpr int const &x() const noexcept { return m_x; }

        constexpr int &x() noexcept { return m_x; }

        [[nodiscard]] constexpr int const &y() const { return m_y; }

        constexpr int &y() noexcept { return m_y; }

        [[nodiscard]] const BoardCaseType &type() const noexcept { return m_type; }

        BoardCaseType &type() noexcept { return m_type; }

        [[nodiscard]] std::optional<SpriteAnimation> const &animation() const noexcept { return m_animation; }

        std::optional<SpriteAnimation> &animation() noexcept { return m_animation; };

        [[nodiscard]] Position position() const noexcept { return {m_x, m_y}; }

        [[nodiscard]] inline bool isTunnel() const noexcept {
            return m_type == BoardCaseType::GhostTunnelSlowDown
                   || m_type == BoardCaseType::DoorLeft
                   || m_type == BoardCaseType::DoorRight;
        }

        static inline bool isPracticable(BoardCase p_boardCase) noexcept {
            return isTypePracticable(p_boardCase.type());
        }

        static inline bool isTypePracticable(BoardCaseType p_boardCaseType) noexcept {
            return p_boardCaseType == BoardCaseType::PointPath
                   || p_boardCaseType == BoardCaseType::BasicPath
                   || p_boardCaseType == BoardCaseType::Bonus
                   || p_boardCaseType == BoardCaseType::DoorLeft
                   || p_boardCaseType == BoardCaseType::DoorRight
                   || p_boardCaseType == BoardCaseType::GhostUpForbidden
                   || p_boardCaseType == BoardCaseType::GhostTunnelSlowDown;
        }

    };

    using DirectionBoardCasePair = std::pair<Direction, std::optional<BoardCase>>;

    [[nodiscard]] static DirectionBoardCasePair
    getClosestBoardCase(Position p_target, std::span<const DirectionBoardCasePair> p_boardCases) noexcept;


}