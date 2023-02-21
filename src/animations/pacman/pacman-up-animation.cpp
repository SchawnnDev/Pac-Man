#include "animations/pacman/pacman-up-animation.h"

PacmanUpAnimation::PacmanUpAnimation(std::vector<Sprite> &&sprites)
        : SpriteAnimation{std::move(sprites)}
{
}

std::optional<Sprite> PacmanUpAnimation::display()
{
    return std::nullopt;
}

void PacmanUpAnimation::start()
{
    SpriteAnimation::start();
}

