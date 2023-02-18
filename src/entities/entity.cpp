#include "../../include/entities/entity.h"
#include "../../include/board/board.h"

void Entity::move(Direction newDirection) {
    // Only be able to change position if the entity is one middle of case
    if (!board()->canEntityMoveTo(this, newDirection) || !Board::isCaseCenter(m_position))
        return;
    direction() = newDirection;
}

void Entity::draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) {
    auto sprite = m_currentAnimation->display();
    if (sprite == nullptr || !m_currentAnimation->activated()) return;
    // TODO: position may be wrong (seen by pixel)
    SDL_Rect destination{m_position.x(), m_position.y(), sprite->rect().w * 4, sprite->rect().h * 4};
    SDL_RenderCopy(p_window_renderer, p_texture, &sprite->rect(), &destination);
}
