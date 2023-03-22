#include "entities/fruit.h"

using namespace pacman;

Fruit::Fruit(Board const &p_board, FruitResources p_fruitResources)
    : Entity{{10, 15}, 0, Direction::LEFT, p_board}
    , m_ticks{0}
    , m_fruitResources{p_fruitResources}
{
    reset();
}

void Fruit::tick() noexcept
{
    if(!activated()) return;
}

void Fruit::changeAnimation() noexcept
{

}

void Fruit::reset() noexcept
{
    currentAnimation() = std::nullopt;
    activated() = false;
    m_ticks = 0;
}