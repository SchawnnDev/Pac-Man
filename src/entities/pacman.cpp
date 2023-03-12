#include "entities/pacman.h"

using namespace pacman;

Pacman::Pacman(const Board &p_board, PacmanAnimations p_pacmanAnimations)
        : Entity(getPosition(10, 20), 1, Direction::LEFT, p_board),
          m_state{PacmanState::LIVING},
          m_animations(std::move(p_pacmanAnimations))
{
    currentAnimation() = m_animations.leftAnimation;
    speed() = 4;
}

void Pacman::tick() noexcept
{
    if (freezed() || !activated()) return;

    if (m_state == PacmanState::DYING)
    {
        return;
    }

    if (!Board::isCase(position()))
    {
        position().moveAt(direction(), speed());
    } else
    {
        if (canMoveTo(direction()))
        {
            position().moveAt(direction(), speed());
        } else
        {
            // Check if user is at doors, then teleport
            if (board().isOnLeftDoor(position()))
            {
                auto const &boardCase = board().grid()[board().rightDoorIndex()];
                position() = getPosition(boardCase.x(), boardCase.y());
            } else if (board().isOnRightDoor(position()))
            {
                auto const &boardCase = board().grid()[board().leftDoorIndex()];
                position() = getPosition(boardCase.x(), boardCase.y());
            } else
            {
                currentAnimation()->freeze() = true;
            }

        }
    }

}

void Pacman::changeAnimation() noexcept
{
    currentAnimation()->freeze() = false;

    switch (direction())
    {
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

void Pacman::reset() noexcept
{
    position() = getPosition(10, 20);
    direction() = Direction::LEFT;
    m_state = PacmanState::LIVING;
    currentAnimation() = m_animations.leftAnimation;
    speed() = 4;
}

Pacman::~Pacman() = default;
