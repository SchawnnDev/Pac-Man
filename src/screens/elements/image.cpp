#include "screens/elements/image.h"

using namespace pacman;

void Image::draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture)
{
    if (!activated()) return;
    SDL_SetTextureColorMod(p_texture, m_color.r, m_color.g, m_color.b);
    SDL_Rect rect{m_position.x(), m_position.y(), m_size.x(), m_size.y()};
    SDL_RenderCopy(p_window_renderer, p_texture, &m_sprite.rect(), &rect);
    SDL_SetTextureColorMod(p_texture, 255, 255, 255);
}
