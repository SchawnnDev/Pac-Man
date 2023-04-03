#include <unordered_map>
#include <iostream>
#include <algorithm>
#include "screens/elements/text.h"

using namespace pacman;

void Text::draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept
{
    if (!activated()) return;
    auto pos = position();

    SDL_SetTextureColorMod(p_texture, m_color.r, m_color.g, m_color.b);

    std::for_each(m_text.cbegin(), m_text.cend(), [this, &p_window_renderer, &p_texture, &pos](auto p_char) {
        if (auto it = m_textResources.alphabetSprites.find(p_char); it != std::end(m_textResources.alphabetSprites))
        {
            auto rect = pos.toSDLRect();
            rect.h = m_size;
            rect.w = m_size; // TODO: handle width
            SDL_RenderCopy(p_window_renderer, p_texture, &it->second.rect(), &rect);
        }
        pos.moveAt(Direction::RIGHT, m_spacing + m_size);
    });

    SDL_SetTextureColorMod(p_texture, 255, 255, 255);

}
