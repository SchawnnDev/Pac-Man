#pragma once

#include <SDL_rect.h>
#include "../sprite.h"
#include "../sprite-animation.h"

enum class EntityType {
    Banana,
    Ghost,
    Fruit
};

class Entity {
    std::shared_ptr<SpriteAnimation> m_currentAnimation;
public:
    Entity(int x, int y);

    virtual ~Entity();

    virtual void Tick() = 0;

    // wow modern (uses cpp move semantics)
    virtual EntityType entityType() const = 0;

    const std::shared_ptr<SpriteAnimation> &currentAnimation() const { return m_currentAnimation; };
    std::shared_ptr<SpriteAnimation> &currentAnimation() { return m_currentAnimation; };

};