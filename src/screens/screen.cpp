#include "screens/screen.h"

using namespace pacman;

void Screen::draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept {

    for (std::pair<SDL_Rect, SDL_Rect> rect : m_tiles) {
        SDL_RenderCopy(p_window_renderer, p_texture,&rect.first, &rect.second);
    }

    for(auto& text : m_texts) {
        text.draw(p_window_renderer, p_texture);
    }

}