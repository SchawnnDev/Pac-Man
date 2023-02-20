#include "entities/entity.h"

void Entity::move(Direction newDirection) {
    // Only be able to change position if the entity is one middle of case
    if (!canMoveTo(newDirection) || !Board::isCaseCenter(m_position))
        return;
    direction() = newDirection;
}

void Entity::draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) {
    if(!m_currentAnimation.has_value()) return;
    auto sprite = m_currentAnimation.value()->display();
    if (!sprite.has_value() || !m_currentAnimation.value()->activated()) return;
    // TODO: position may be wrong (seen by pixel)
    SDL_Rect destination{m_position.x(), m_position.y(), sprite->rect().w * 4, sprite->rect().h * 4};
    SDL_RenderCopy(p_window_renderer, p_texture, &sprite->rect(), &destination);
}

bool Entity::canMoveTo(Direction p_direction) const {
    auto caseFound = Board::findCase(position());
    if (caseFound.x() == -1 || caseFound.y() == -1) return false;
    auto nextCasePos = caseFound.getPositionAt(p_direction);
    return BoardCase::isPracticable(board().getCase(nextCasePos.x(), nextCasePos.y()));
}