#include "entities/fruit.h"

using namespace pacman;

Fruit::Fruit(Board const &p_board, FruitResources p_fruitResources)
    : Entity{getPosition(10, 15), 0, Direction::LEFT, p_board}
    , m_ticks{0}
    , m_score{false}
    , m_fruitResources{p_fruitResources}
{
    Fruit::reset();
}

void Fruit::tick()
{
    if(!activated()) return;

    // Score stays for 3 secs, fruit for 10 secs
    auto const delay = FRAMERATE * (m_score ? 3 : 10);

    if(m_ticks >= delay) {
        reset();
        return;
    }

    m_ticks++;
}

void Fruit::changeAnimation()
{

}

void Fruit::reset()
{
    currentAnimation() = std::nullopt;
    activated() = false;
    m_score = false;
    m_ticks = 0;
}

void Fruit::display(int p_level)
{
    activated() = true;
    currentAnimation() = SpriteAnimation{{m_fruitResources.fruitsSprites[getFruitByLevel(p_level)]}, false, 1, true, true};
}

void Fruit::eat(int p_score)
{
    if(!activated() || m_score) return;
    if (auto it = m_fruitResources.m_scoresSprites.find(p_score); it != std::end(m_fruitResources.m_scoresSprites))
    {
        activated() = true;
        currentAnimation() = SpriteAnimation{{it->second}, false, 1, true, true};
        m_ticks = 0;
        m_score = true;
    } else
    {
        reset();
    }
}
