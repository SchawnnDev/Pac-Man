#pragma once

#include <memory>
#include <utility>
#include <vector>

#include <SDL_render.h>

#include "sprite.h"
#include "sprite-resources-structs.h"
#include "utils/position.h"
#include "drawable.h"

namespace pacman {

    constexpr int strTextSize(int p_strLen, int p_charSize, int p_spacing)
    {
        return p_strLen * p_charSize + std::max(0, p_strLen - 1) * p_spacing;
    }

    constexpr int strTextSize(std::string_view p_str, int p_charSize, int p_spacing)
    {
        return strTextSize(p_str.length(), p_charSize, p_spacing);
    }

    class Text : public Drawable {
        std::vector<Sprite> m_sprites;
        std::string m_text;
        TextResources m_textResources;
        int m_spacing;
        int m_size;
        Position m_position;
        SDL_Color m_color;
    public:
        Text(std::string p_text, Position p_position, int p_size, int p_spacing, TextResources p_textResources)
        : m_text{std::move(p_text)}
        , m_sprites{}
        , m_textResources{p_textResources}
        , m_size{p_size}
        , m_spacing{p_spacing}
        , m_position{p_position}
        , m_color{255,255,255}
        {}

        [[nodiscard]] std::string const& text() const noexcept { return m_text; }
        std::string &text() noexcept { return m_text; }
        [[nodiscard]] int spacing() const noexcept { return m_spacing; }
        int& spacing() noexcept { return m_spacing; }
        [[nodiscard]] int size() const noexcept { return m_size; }
        int& size() noexcept { return m_size; }
        [[nodiscard]] Position const& position() const noexcept { return m_position; }
        Position &position() noexcept { return m_position; }
        SDL_Color &color() noexcept { return m_color; }
        [[nodiscard]] inline int textSize() const {
            return strTextSize(m_text, m_size, m_spacing);
        }

        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept override;
    };

    using TextElement = std::shared_ptr<Text>;

}
