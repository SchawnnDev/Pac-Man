#include "../../../include/animations/pacman/pacman-right-animation.h"

PacmanRightAnimation::PacmanRightAnimation()
        : SpriteAnimation({"pacman_dying_1", "pacman_dying_2", "pacman_dying_3",
                           "pacman_dying_4", "pacman_dying_5", "pacman_dying_6",
                           "pacman_dying_7", "pacman_dying_8", "pacman_dying_9", "pacman_dying_10"}) {
    m_ticks = -1;
}

PacmanRightAnimation::~PacmanRightAnimation() {

}

std::optional<Sprite> PacmanRightAnimation::display() {
    if(!activated()) return std::nullopt;
    m_ticks++;

    // first tick
    if(m_ticks <= 0)
    {
        return sprites()[0];
    }

    int idx = m_ticks / 6;

    if(idx > 9)
    {
        activated() = false;
        return std::nullopt;
    }

    return sprites()[idx];
}

void PacmanRightAnimation::start() {
    if(activated()) return;
    SpriteAnimation::start();
    m_ticks = -1;
}

