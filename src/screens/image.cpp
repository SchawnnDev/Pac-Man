#include "screens/image.h"

using namespace pacman;

void Image::draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept {
    if (!activated()) return;
    SDL_Rect rect{m_position.x(), m_position.y(), m_size.x(), m_size.y()};
    SDL_RenderCopy(p_window_renderer, p_texture, &m_sprite.rect(), &rect);
}
