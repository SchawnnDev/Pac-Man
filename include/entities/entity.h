#pragma once

#include <SDL_rect.h>
#include "../sprite.h"
#include "../sprite-animation.h"

enum class EntityType {
    Banana,
    Ghost,
    Fruit
};

class Entity : public SpriteAnimation {
public:
    Entity(int x, int y);

    virtual ~Entity();

    virtual void Tick() = 0;

    // wow modern (uses cpp move semantics)
    virtual EntityType entityType() const = 0;

};