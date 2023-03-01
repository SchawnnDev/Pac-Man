#pragma once

#include "sprite-animation.h"
#include "utils/position.h"

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
    Nothing
};

class BoardCase {
    int m_x;
    int m_y;
    BoardCaseType m_type;
    std::optional<SpriteAnimation> m_animation;
public:
    BoardCase() : m_x(0), m_y(0), m_type(BoardCaseType::PointPath) {}

    ~BoardCase();

    BoardCase(const int &p_x, const int &p_y, const BoardCaseType &p_type,
              const std::optional<SpriteAnimation> &p_animation) : m_x(p_x), m_y(p_y), m_type(p_type),
                                                                   m_animation(p_animation) {}

    [[nodiscard]] constexpr int const &x() const { return m_x; }

    constexpr int &x() { return m_x; }

    [[nodiscard]] constexpr int const &y() const { return m_y; }

    constexpr int &y() { return m_y; }

    [[nodiscard]] const BoardCaseType &type() const { return m_type; }

    BoardCaseType &type() { return m_type; }

    [[nodiscard]] std::optional<SpriteAnimation> const &animation() const { return m_animation; }

    std::optional<SpriteAnimation> &animation() { return m_animation; };

    [[nodiscard]] Position position() const { return {m_x, m_y}; }

    static inline bool isPracticable(BoardCase p_boardCase) {
        return isTypePracticable(p_boardCase.type());
    }

    static inline bool isTypePracticable(BoardCaseType p_boardCaseType) {
        return p_boardCaseType == BoardCaseType::PointPath
               || p_boardCaseType == BoardCaseType::BasicPath
               || p_boardCaseType == BoardCaseType::Bonus
               || p_boardCaseType == BoardCaseType::DoorLeft
               || p_boardCaseType == BoardCaseType::DoorRight;
    }

};

template<typename... Args>
requires (... && std::convertible_to<Args, std::pair<Direction, std::optional<BoardCase>>>)
[[nodiscard]]
auto getClosestBoardCase(Position p_target, Args... p_boardCases) noexcept {
    std::array<std::pair<Direction, std::optional<BoardCase>>, sizeof...(p_boardCases)> boardCases = {
            {p_boardCases...}};
    std::pair<Direction, std::optional<BoardCase>> result{Direction::DOWN, std::nullopt};
    int distanceTo = -1;

    for (const std::pair<Direction, std::optional<BoardCase>> &pair: boardCases) {
        auto boardCase = pair.second;
        if (!boardCase || !BoardCase::isPracticable(boardCase.value())) continue;

        auto distance = boardCase.value().position().distanceTo(p_target);

        if (result.second) {
            if (distance < distanceTo) {
                distanceTo = distance;
                result = pair;
            } else if (distance == distanceTo &&
                       getDirectionPriority(pair.first) > getDirectionPriority(result.first)) {
                // check priority of directions
                result = pair;
            }
        } else {
            result = pair;
            distanceTo = distance;
        }

    }

    return result;
}