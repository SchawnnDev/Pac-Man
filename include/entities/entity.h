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
    Direction m_lastDirection;
    Position m_position;
    int m_speed; // speed in pixel per tick
public:

    Entity() = delete;

    Entity(Position p_position, int p_speed, Direction p_direction, const Board& p_board)
    : m_position{p_position}
    , m_direction{p_direction}
    , m_speed{p_speed}
    , m_board{p_board}
    , m_lastDirection{p_direction}
    {}

    virtual ~Entity() = default;

    virtual void tick() = 0;

    // wow, modern (uses cpp move semantics)
    [[nodiscard]] virtual EntityType entityType() const = 0;

    [[nodiscard]] std::optional<SpriteAnimation> const& currentAnimation() const { return m_currentAnimation; };

    std::optional<SpriteAnimation> &currentAnimation() { return m_currentAnimation; };

    [[nodiscard]] Board const& board() const { return m_board; };

    Board &board() { return m_board; };

    [[nodiscard]] Direction const& direction() const { return m_direction; };

    Direction &direction() { return m_direction; };

    [[nodiscard]] Direction const& lastDirection() const { return m_lastDirection; };

    Direction &lastDirection() { return m_lastDirection; };

    [[nodiscard]] Position const& position() const { return m_position; };

    Position &position() { return m_position; };

    void move(Direction newDirection);

    void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture);

    [[nodiscard]] bool canMoveTo(Direction p_direction) const;


};