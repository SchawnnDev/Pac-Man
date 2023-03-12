#include "screens/game-screen.h"
#include "utils/shared_value.h"
#include "level.h"

using namespace pacman;

GameScreen::GameScreen(TextResources p_textResources, shared_value<LevelState> const& p_levelState)
    : Screen(p_textResources)
        , m_player{std::make_shared<Text>("player one", Position{m_winMiddleX - CALC(5), m_winMiddleY - 90}, m_charSize, m_spacing, p_textResources)}
        , m_ready{std::make_shared<Text>("ready!", Position{m_winMiddleX - CALC(3), m_winMiddleY + 70}, m_charSize, m_spacing, p_textResources)}
        , m_levelState{p_levelState}
{
    m_player->color() = {0,255,255};
    m_ready->color() = {240,188,60};
    addElement(m_player);
    addElement(m_ready);
    GameScreen::reset();
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

void GameScreen::updateState()
{
    disable();

    if(m_levelState == LevelState::PlayerDisplay)
    {
        m_player->activated() = true;
        m_ready->activated() = true;
        return;
    }

    if(m_levelState == LevelState::Ready)
    {
        m_player->activated() = false;
        m_ready->activated() = true;
        return;
    }

}
