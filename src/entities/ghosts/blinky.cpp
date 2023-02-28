#include "entities/ghosts/blinky.h"

void Blinky::tick() {

    if(lastDirection() != direction())
    {

        switch (direction()) {
            case Direction::UP:
                currentAnimation() = m_animations.upAnimation;
                break;
            case Direction::DOWN:
                currentAnimation() = m_animations.downAnimation;
                break;
            case Direction::LEFT:
                currentAnimation() = m_animations.leftAnimation;
                break;
            case Direction::RIGHT:
                currentAnimation() = m_animations.rightAnimation;
                break;
        }

    }

    if(ghostMode() == GhostMode::Scatter)
    {

    }

}

Blinky::~Blinky() = default;
