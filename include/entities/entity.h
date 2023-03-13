#pragma once

#include <SDL_rect.h>
#include <SDL.h>
#include "sprite.h"
#include "sprite-animation.h"
#include "utils/position.h"
#include "board/board.h"

namespace pacman {

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

        virtual void tick() noexcept = 0;

        virtual void changeAnimation() noexcept = 0;

        virtual void reset() noexcept = 0;

        // wow, modern (uses cpp move semantics)
        [[nodiscard]] virtual EntityType entityType() const noexcept = 0;

        [[nodiscard]] std::optional<SpriteAnimation> const &currentAnimation() const noexcept { return m_currentAnimation; };

        std::optional<SpriteAnimation> &currentAnimation() noexcept { return m_currentAnimation; };

        [[nodiscard]] Board const &board() const noexcept { return m_board; };

        Board &board() noexcept { return m_board; };

        [[nodiscard]] Direction direction() const noexcept { return m_direction; };

        Direction &direction() noexcept { return m_direction; };

        [[nodiscard]] Position position() const noexcept { return m_position; };

        Position &position() noexcept { return m_position; };

        [[nodiscard]] std::optional<BoardCase> const &currentCase() const noexcept { return m_currentCase; };

        std::optional<BoardCase> &currentCase() noexcept { return m_currentCase; };

        [[nodiscard]] int speed() const noexcept { return m_speed; }

        int &speed() noexcept { return m_speed; }

        [[nodiscard]] bool freezed() const noexcept { return m_freeze; }

        void move(Direction newDirection) noexcept;

        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept override;

        [[nodiscard]] bool canMoveTo(Direction p_direction) const noexcept;

        [[nodiscard]] bool isGhost() const noexcept;

        void freeze() noexcept;

        void unfreeze() noexcept;

    };

}