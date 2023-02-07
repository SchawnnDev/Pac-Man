#pragma once

#include <SDL_rect.h>
#include <string>

class Sprite {
    SDL_Rect m_rect;
    std::string m_name;

public:
    explicit Sprite(const std::string& name);
    ~Sprite();

    std::string const &name() const { return m_name; };
    std::string &name() { return m_name; };

    SDL_Rect const &rect() const { return m_rect; };
    SDL_Rect &rect() { return m_rect; };

};