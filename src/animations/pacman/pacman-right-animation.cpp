#include "animations/pacman/pacman-right-animation.h"

PacmanRightAnimation::PacmanRightAnimation(std::vector<Sprite> &&args)
        : SpriteAnimation{std::move(args)}, m_ticks{-1}
{}

std::optional<Sprite> PacmanRightAnimation::display()
{
    if (!activated()) return std::nullopt;
    m_ticks++;

    // first tick
    if (m_ticks <= 0)
    {
        return sprites()[0];
    }

    int idx = m_ticks / 6;

    if (idx > 9)
    {
        activated() = false;
        return std::nullopt;
    }

    return sprites()[idx];
}

void PacmanRightAnimation::start()
{
    if (activated()) return;
    SpriteAnimation::start();
    m_ticks = -1;
}

