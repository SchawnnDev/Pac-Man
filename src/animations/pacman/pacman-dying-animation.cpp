#include "animations/pacman/pacman-dying-animation.h"

PacmanDyingAnimation::PacmanDyingAnimation(std::vector<Sprite> &&args)
        : SpriteAnimation{std::move(args)}, m_ticks{-1}
{}

std::optional<Sprite> PacmanDyingAnimation::display()
{
    if (!activated()) return std::nullopt;
    m_ticks++;

    // TODO: implement freeze

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

void PacmanDyingAnimation::start()
{
    if (activated()) return;
    SpriteAnimation::start();
    m_ticks = -1;
}
