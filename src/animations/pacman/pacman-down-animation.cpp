#include "animations/pacman/pacman-down-animation.h"

PacmanDownAnimation::PacmanDownAnimation(std::vector<Sprite> &&sprites)
        : SpriteAnimation{std::move(sprites)}
{

}

std::optional<Sprite> PacmanDownAnimation::display()
{
    return std::nullopt;
}

void PacmanDownAnimation::start()
{
    SpriteAnimation::start();
}
