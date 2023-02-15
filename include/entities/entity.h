#pragma once

#include <SDL_rect.h>
#include "../sprite.h"
#include "../sprite-animation.h"
#include "../utils/position.h"

enum class EntityType {
    Banana,
    Ghost,
    Fruit
};

class Entity {
    std::shared_ptr<SpriteAnimation> m_currentAnimation;
    Direction m_direction;
    Position m_position;
    int m_speed; // speed in pixel per tick
public:

    Entity() = default;

    Entity(int p_x, int p_y, int p_speed, Direction p_direction) : m_position({p_x, p_y}), m_direction(p_direction), m_speed(p_speed) {}

    virtual ~Entity();

    virtual void Tick() = 0;

    // wow, modern (uses cpp move semantics)
    [[nodiscard]] virtual EntityType entityType() const = 0;

    [[nodiscard]] const std::shared_ptr<SpriteAnimation> &currentAnimation() const { return m_currentAnimation; };

    std::shared_ptr<SpriteAnimation> &currentAnimation() { return m_currentAnimation; };

    [[nodiscard]] const Direction &direction() const { return m_direction; };

    Direction &direction() { return m_direction; };

    [[nodiscard]] const Position &position() const { return m_position; };

    Position &position() { return m_position; };


};