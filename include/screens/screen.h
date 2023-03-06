#pragma once

#include <SDL_render.h>
#include <utility>
#include <vector>
#include "sprite-resources-structs.h"
#include "text.h"

namespace pacman {

    class Screen {
        int m_ticks;
        std::vector<std::pair<SDL_Rect, SDL_Rect>> m_tiles;
        std::vector<Text> m_texts;
        TextResources m_textResources;
    public:
        explicit Screen(TextResources p_textResources)
        : m_ticks{0}, m_tiles{}, m_texts{}, m_textResources{std::move(p_textResources)} {};

        ~Screen() = default;

        [[nodiscard]] int ticks() const noexcept { return m_ticks; }

        int &ticks() noexcept { return m_ticks; }

        virtual void tick() noexcept = 0;

        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept;

    };

}