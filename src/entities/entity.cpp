#include "entities/entity.h"

using namespace pacman;

void Entity::move(Direction newDirection) noexcept {
    if(m_freeze || !activated()) return;
    // If entity walks in the same direction, check if
    // Only be able to change position if the entity is one middle of case
    if (!canMoveTo(newDirection) || !Board::isCase(m_position)
                                    && getOpposite(direction()) != newDirection)
        return;

    direction() = newDirection;
    changeAnimation();
}

void Entity::draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept {
    if(!activated()) return;
    if (!m_currentAnimation) return;
    auto &spriteAnimation = m_currentAnimation.value();
    auto sprite = spriteAnimation.display();
    if (!sprite.has_value() || !m_currentAnimation.value().activated()) return;
    // TODO: position may be wrong (seen by pixel)
    SDL_Rect destination{m_position.x(), m_position.y(), BOARD_CASE_SIZE_WIDTH, BOARD_CASE_SIZE_HEIGHT};
    SDL_RenderCopy(p_window_renderer, p_texture, &sprite->rect(), &destination);
}

bool Entity::canMoveTo(Direction p_direction) const noexcept {
    auto caseFound = Board::findCase(position());
    if (caseFound.x() == -1 || caseFound.y() == -1) return false;
    auto nextCasePos = caseFound.getPositionAt(p_direction, 1);
    if (!Board::checkGridCoordinates(nextCasePos)) return false;
    return BoardCase::isPracticable(board().getCase(nextCasePos));
}

void Entity::freeze() noexcept {
    m_freeze = true;
    if(m_currentAnimation) {
        m_currentAnimation->freeze() = true;
    }
}

void Entity::unfreeze() noexcept {
    m_freeze = false;
    if(m_currentAnimation) {
        m_currentAnimation->freeze() = false;
    }
}

void Entity::freezeMovement() noexcept {
    m_freeze = true;
}

void Entity::unfreezeMovement() noexcept {
    m_freeze = false;
}

bool Entity::isGhost() const noexcept {
    const auto type = entityType();
    return type == EntityType::Blinky
           || type == EntityType::Clyde
           || type == EntityType::Pinky
           || type == EntityType::Inky;
}

bool Entity::checkCollision(Position p_topLeft, Position p_bottomRight) const noexcept
{
    int m_x1 = m_position.x();
    int m_y1 = m_position.y();
    int m_x2 = m_x1 + 32;
    int m_y2 = m_y1 + 32;
    return (m_x1 < p_bottomRight.x()) && (m_x2 > p_topLeft.x()) && (m_y1 < p_bottomRight.y()) && (m_y2 > p_topLeft.y());
}

bool Entity::checkCollision(const Entity &p_with) const noexcept
{
    if(!activated() || !p_with.activated()) return false;
    Position first{};
    Position sec{};
    auto const position = p_with.position();
    int const halfX = BOARD_CASE_SIZE_WIDTH / 2;
    int const halfY = BOARD_CASE_SIZE_HEIGHT / 2;

    switch (m_direction)
    {
        case Direction::UP:
            first = position.add({0, halfY});
            sec = position.add({BOARD_CASE_SIZE_WIDTH, BOARD_CASE_SIZE_HEIGHT});
            break;
        case Direction::DOWN:
            first = position;
            sec = position.add({BOARD_CASE_SIZE_WIDTH, BOARD_CASE_SIZE_HEIGHT});
            break;
        case Direction::LEFT:
            first = position;
            sec = position.add({halfX, BOARD_CASE_SIZE_HEIGHT});
            break;
        case Direction::RIGHT:
            first = position.add({halfX, 0});
            sec = position.add({BOARD_CASE_SIZE_WIDTH, BOARD_CASE_SIZE_HEIGHT});
            break;
    }

    return checkCollision(first, sec);
}
