#pragma once

#include "sprites/sprite-animation.h"
#include "utils/position.h"
#include "screens/drawable.h"

namespace pacman {

    /**
     *  @brief Type of the case, to distinguish between doors, walls, points,...
     */
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

    /**
     * @inherit Drawable
     */
    class BoardCase : public Drawable {
        int m_x;
        int m_y;
        BoardCaseType m_type;
        uint8_t m_flags;
        std::optional<SpriteAnimation> m_currentAnimation;
    public:
        BoardCase() : m_x{0}, m_y{0}, m_flags{0}, m_type(BoardCaseType::PointPath) {}

        ~BoardCase() = default;

        BoardCase(int p_x, int p_y, BoardCaseType p_type,
                  uint8_t flags, const std::optional<SpriteAnimation> &p_animation)
                  : m_x{p_x}, m_y{p_y}, m_type{p_type}, m_flags{flags}, m_currentAnimation(p_animation) {}

        /**
         * @return X index
         */
        [[nodiscard]] constexpr int x() const noexcept { return m_x; }

        /**
         * @return Reference to X index
         */
        constexpr int &x() noexcept { return m_x; }

        /**
         * @return Y index
         */
        [[nodiscard]] constexpr int y() const { return m_y; }

        /**
         * @return Reference to y index
         */
        constexpr int &y() noexcept { return m_y; }

        /**
         * @brief Flags represent some infos about cases, like no_up or tunnel_slowdown
         * @return This case flags
         */
        [[nodiscard]] constexpr uint8_t flags() const { return m_flags; }

        /**
         * @brief Flags represent some infos about cases, like no_up or tunnel_slowdown
         * @return Reference to flags
         */
        constexpr uint8_t& flags() { return m_flags; }

        /**
         * @return Type of this case
         */
        [[nodiscard]] BoardCaseType type() const noexcept { return m_type; }

        /**
         * @return Reference to the type of this case
         */
        BoardCaseType &type() noexcept { return m_type; }

        /**
         * @return Current sprite currentAnimation of this case (optional)
         */
        [[nodiscard]] std::optional<SpriteAnimation> const &currentAnimation() const noexcept { return m_currentAnimation; }

        /**
         * @return Reference to the current sprite currentAnimation of this case (optional)
         */
        std::optional<SpriteAnimation> &currentAnimation() noexcept { return m_currentAnimation; };

        /**
         * @return (x, y) position of case on board (not pixels)
         */
        [[nodiscard]] Position position() const noexcept { return {m_x, m_y}; }

        /**
         * @brief Draw boardcase to screen
         * @param p_window_renderer Window renderer
         * @param p_texture Texture to get sprite from
         * @override
         */
        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept override;

        /**
         * @param p_boardCase BoardCase to check
         * @return BoardCaseType of p_boardCase is practicable by an entity (to avoid going in walls cases)
         */
        static inline bool isPracticable(BoardCase p_boardCase) noexcept {
            return isTypePracticable(p_boardCase.type());
        }

        /**
         * @param p_boardCaseType BoardCaseType to check
         * @return BoardCaseType is practicable by an entity (to avoid going in walls cases)
         */
        static constexpr bool isTypePracticable(BoardCaseType p_boardCaseType) noexcept {
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