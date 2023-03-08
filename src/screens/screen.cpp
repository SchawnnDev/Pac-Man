#include "screens/screen.h"

using namespace pacman;

void Screen::draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept {
    for(auto& tile : m_elements) {
        tile->draw(p_window_renderer, p_texture);
    }
}