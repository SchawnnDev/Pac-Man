#pragma once

#include <utility>
#include <vector>
#include <SDL_render.h>
#include "sprite.h"
#include "sprite-resources-structs.h"
#include "utils/position.h"

namespace pacman {
    class Text {
        std::vector<Sprite> m_sprites;
        std::string m_text;
        TextResources m_textResources;
        int m_spacing;
        int m_size;
        Position m_position;
        bool m_display;
    public:
        Text(std::string p_text, Position p_position, int p_size, int p_spacing, TextResources p_textResources)
        : m_text{std::move(p_text)}
        , m_sprites{}
        , m_textResources{std::move(p_textResources)}
        , m_size{p_size}
        , m_spacing{p_spacing}
        , m_position{p_position}
        , m_display{true}
        {
            parse();
        }

        [[nodiscard]] std::string const& text() const noexcept { return m_text; }
        [[nodiscard]] int spacing() const noexcept { return m_spacing; }
        int& spacing() noexcept { return m_spacing; }
        [[nodiscard]] int size() const noexcept { return m_size; }
        int& size() noexcept { return m_size; }
        [[nodiscard]] Position const& position() const noexcept { return m_position; }
        Position &position() noexcept { return m_position; }
        [[nodiscard]] bool display() const noexcept { return m_display; }
        bool &display() noexcept { return m_display; }

        void parse() noexcept;

        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept;
    };
}