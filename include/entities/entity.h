#pragma once
#include <SDL_rect.h>

enum class EntityType {
    Banana,
    Ghost,
    Fruit
};

class Entity {
    SDL_Rect m_rect;
public:
    Entity(int x, int y);
    virtual ~Entity();
    virtual void Tick() = 0;

    SDL_Rect const &rect() const { return m_rect; };
    SDL_Rect &rect() { return m_rect; };

    // wow modern (uses cpp move semantics)
    virtual EntityType entityType() const = 0;

};