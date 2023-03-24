#pragma once

#include <SDL_rect.h>
#include <SDL.h>
#include "sprites/sprite.h"
#include "sprites/sprite-animation.h"
#include "utils/position.h"
#include "board/board.h"

namespace pacman {

    /**
     * @brief All possible entities
     */
    enum class EntityType {
        Pacman,
        Blinky,
        Pinky,
        Clyde,
        Inky,
        Fruit
    };

    class Entity : public Drawable {
        Board m_board;
        std::optional<SpriteAnimation> m_currentAnimation;
        Direction m_direction;
        Position m_position;
        std::optional<BoardCase> m_currentCase;
        int m_speed; // speed in pixel per tick
        bool m_freeze;
    public:

        Entity() = delete;

        Entity(Position p_position, int p_speed, Direction p_direction, const Board &p_board)
                : m_position{p_position}, m_direction{p_direction}, m_speed{p_speed}, m_board{p_board},
                  m_currentCase{std::nullopt}, m_freeze{false} {}

        virtual ~Entity() = default;

        /**
         * @brief Tick logic, handles intern entities logic
         */
        virtual void tick() noexcept = 0;

        /**
         * @brief Changes animation corresponding to current state
         */
        virtual void changeAnimation() noexcept = 0;

        /**
         * @brief Reset all variables to default
         */
        virtual void reset() noexcept = 0;


        /**
         * @return Type of entity
         */
        [[nodiscard]] virtual EntityType entityType() const noexcept = 0; // wow, modern (uses cpp move semantics)

        /**
         * @return Current sprite animation of entity
         */
        [[nodiscard]] std::optional<SpriteAnimation> const &currentAnimation() const noexcept { return m_currentAnimation; };

        /**
         * @return Reference to the current sprite animation of entity (optional)
         */
        std::optional<SpriteAnimation> &currentAnimation() noexcept { return m_currentAnimation; };

        /**
         * @return Board instance reference
         */
        [[nodiscard]] Board const &board() const noexcept { return m_board; };

        /**
         * @return Reference to the board instance
         */
        Board &board() noexcept { return m_board; };

        /**
         * @return Direction of the entity
         */
        [[nodiscard]] Direction direction() const noexcept { return m_direction; };

        /**
         * @return Reference to the direction of the entity
         */
        Direction &direction() noexcept { return m_direction; };

        /**
         * @return Position of the entity
         */
        [[nodiscard]] Position position() const noexcept { return m_position; };

        /**
         * @return Reference to the position of the entity
         */
        Position &position() noexcept { return m_position; };

        /**
         * @return Current case the entity is staying on
         */
        [[nodiscard]] std::optional<BoardCase> const &currentCase() const noexcept { return m_currentCase; };

        /**
         * @return Reference to current case the entity is staying on
         */
        std::optional<BoardCase> &currentCase() noexcept { return m_currentCase; };

        /**
         * @return Speed of entity in pixels per tick
         */
        [[nodiscard]] int speed() const noexcept { return m_speed; }

        /**
         * @brief Speed of entity in pixels per tick
         * @return Reference to speed
         */
        int &speed() noexcept { return m_speed; }

        /**
         * @return Entity is freezed or not
         */
        [[nodiscard]] bool freezed() const noexcept { return m_freeze; }

        /**
         * @brief Move this entity to a new direction
         * @param newDirection The new direction to move to
         */
        void move(Direction newDirection) noexcept;

        /**
         * @brief Draw this entity to screen
         * @param p_window_renderer Window renderer
         * @param p_texture Texture to get sprite from
         */
        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept override;

        /**
         * @param p_direction Direction to move to
         * @return Checks whether this entity can move in p_direction or not
         */
        [[nodiscard]] bool canMoveTo(Direction p_direction) const noexcept;

        /**
         * @return Checks whether the entity is a ghost or not
         */
        [[nodiscard]] bool isGhost() const noexcept;

        /**
         * @brief Freeze entity (movement + animations + logic)
         */
        void freeze() noexcept;

        /**
         * @brief Unfreeze entity (movement + animations + logic)
         */
        void unfreeze() noexcept;

        /**
         * @brief Freezes entities movement (animation still activated)
         */
        void freezeMovement() noexcept;

        /**
         * @brief Unfreeze entities movement
         */
        void unfreezeMovement() noexcept;

        /**
         * @param p_topLeft Top left position of rectangle
         * @param p_bottomRight Bottom right position of rectangle
         * @return Checks collisions between this entity and (p_topLeft, p_bottomRight) rectangle
         */
        [[nodiscard]] bool checkCollision(Position p_topLeft, Position p_bottomRight) const noexcept;

        /**
         * @param p_with Entity to check collision with
         * @return Checks if this entity collides p_with entity
         */
        [[nodiscard]] bool checkCollision(Entity const& p_with) const noexcept;

    };

}