#include "screens/game-screen.h"

using namespace pacman;

GameScreen::GameScreen(TextResources p_textResources)
    : Screen(p_textResources)
        , m_player{std::make_shared<Text>("player one", Position{m_winMiddleX - CALC(10), 120}, m_charSize, m_spacing, p_textResources)}
        , m_ready{std::make_shared<Text>("ready!", Position{m_winMiddleX - CALC(10), 120}, m_charSize, m_spacing, p_textResources)}
{
    addElement(m_player);
    addElement(m_ready);
    reset();
}

void GameScreen::tick() noexcept
{
    if(!activated()) return;
}

void GameScreen::reset() noexcept
{
    disable();
}

void GameScreen::disable() noexcept
{
    m_player->activated() = false;
    m_ready->activated() = false;
}
