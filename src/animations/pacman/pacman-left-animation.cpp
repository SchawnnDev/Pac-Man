#include "animations/pacman/pacman-left-animation.h"

PacmanLeftAnimation::PacmanLeftAnimation(std::vector<Sprite> &&sprites)
        : SpriteAnimation{std::move(sprites)}
{

}

std::optional<Sprite> PacmanLeftAnimation::display()
{
    return std::nullopt;
}

void PacmanLeftAnimation::start()
{
    SpriteAnimation::start();
}
