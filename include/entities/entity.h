#pragma once

#include <SDL_rect.h>
#include <SDL.h>
#include "sprite.h"
#include "sprite-animation.h"
#include "utils/position.h"
#include "board/board.h"

enum class EntityType {
    Banana,
    Ghost,
    Fruit
};

class Entity {
    Board m_board;
    std::optional<SpriteAnimation> m_currentAnimation;
    Direction m_direction;
    Position m_position;
    int m_speed; // speed in pixel per tick
public:

    Entity() = default;

    Entity(int p_x, int p_y, int p_speed, Direction p_direction, const Board& p_board) : m_position(
            {p_x, p_y}), m_direction(p_direction), m_speed(p_speed), m_board(p_board) {}

    virtual ~Entity() = default;

    virtual void tick() = 0;

    // wow, modern (uses cpp move semantics)
    [[nodiscard]] virtual EntityType entityType() const = 0;

    [[nodiscard]] const std::optional<SpriteAnimation> &currentAnimation() const { return m_currentAnimation; };

    std::optional<SpriteAnimation> &currentAnimation() { return m_currentAnimation; };

    [[nodiscard]] const Board &board() const { return m_board; };

    Board &board() { return m_board; };

    [[nodiscard]] const Direction &direction() const { return m_direction; };

    Direction &direction() { return m_direction; };

    [[nodiscard]] const Position &position() const { return m_position; };

    Position &position() { return m_position; };

    void move(Direction newDirection);

    void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture);

    [[nodiscard]] bool canMoveTo(Direction p_direction) const;


};