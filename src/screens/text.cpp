#include "screens/text.h"

using namespace pacman;

void Text::parse() noexcept {
    std::transform(
            m_text.cbegin(), m_text.cend(),
            std::back_inserter(m_sprites), // Write results to vector
            [this](auto p_char) {
                if (auto it = m_textResources.alphabetSprites.find(p_char); it != std::end(
                        m_textResources.alphabetSprites))
                    return it->second;
                return m_textResources.nothingSprite;
            }
    );
}

void Text::draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept {
    if(!m_display) return;
    auto pos = position();

    for (auto& sprite : m_sprites) {
        if(sprite.isNothing()) continue;
        auto rect = pos.toSDLRect();
        rect.h = m_size;
        rect.w = m_size; // TODO: handle width
        SDL_RenderCopy(p_window_renderer, p_texture, &sprite.rect(), &rect);
        pos.moveAt(Direction::RIGHT, m_spacing);
    }

}
