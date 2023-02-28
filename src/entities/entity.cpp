#include "entities/entity.h"

void Entity::move(Direction newDirection) {

    // If entity walks in the same direction, check if
    // Only be able to change position if the entity is one middle of case
    if (!canMoveTo(newDirection) || !Board::isCase(m_position)
                                    && getOpposite(direction()) != newDirection)
        return;

    lastDirection() = direction();
    direction() = newDirection;
    changeAnimation();
}

void Entity::draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) {
    if (!m_currentAnimation) return;
    auto &spriteAnimation = m_currentAnimation.value();
    auto sprite = spriteAnimation.display();
    if (!sprite.has_value() || !m_currentAnimation.value().activated()) return;
    // TODO: position may be wrong (seen by pixel)
    SDL_Rect destination{m_position.x(), m_position.y(), BOARD_CASE_SIZE_WIDTH, BOARD_CASE_SIZE_HEIGHT};
    SDL_RenderCopy(p_window_renderer, p_texture, &sprite->rect(), &destination);
}

bool Entity::canMoveTo(Direction p_direction) const {
    auto caseFound = Board::findCase(position());
    if (caseFound.x() == -1 || caseFound.y() == -1) return false;
    auto nextCasePos = caseFound.getPositionAt(p_direction);
    if (!Board::checkGridCoordinates(nextCasePos)) return false;
    return BoardCase::isPracticable(board().getCase(nextCasePos));
}