#include "screens/game-screen.h"
#include "utils/shared_value.h"
#include "game/level.h"

using namespace pacman;

GameScreen::GameScreen(TextResources p_textResources, shared_value<LevelState> const& p_levelState, shared_value<GameState> const& p_gameState, PlayerPtr& p_currentPlayer)
    : Screen(p_textResources)
        , m_player{std::make_shared<Text>("player one", Position{m_winMiddleX - CALC(5), m_winMiddleY - 90}, m_charSize, m_spacing, p_textResources)}
        , m_ready{std::make_shared<Text>("ready!", Position{m_winMiddleX - CALC(3), m_winMiddleY + 70}, m_charSize, m_spacing, p_textResources)}
        , m_gameOver{std::make_shared<Text>("game  over", Position{m_winMiddleX - CALC(5), m_winMiddleY + 70}, m_charSize, m_spacing, p_textResources)}
        , m_levelState{p_levelState}
        , m_gameState{p_gameState}
        , m_currentPlayer{p_currentPlayer}
{
    m_player->color() = {0, 255, 255};
    m_ready->color() = {240, 188, 60};
    m_gameOver->color() = {216, 40, 0};
    addElement(m_player);
    addElement(m_ready);
    addElement(m_gameOver);
    GameScreen::reset();
}

void GameScreen::tick() {}

void GameScreen::reset()
{
    disable();
}

void GameScreen::disable()
{
    m_player->activated() = false;
    m_ready->activated() = false;
    m_gameOver->activated() = false;
}

void GameScreen::updateState(bool p_playerDisplayGameOver)
{
    disable();

    if(m_gameState == GameState::Playing) {
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

    if(m_gameState == GameState::GameOver)
    {
        m_gameOver->activated() = true;
        if(p_playerDisplayGameOver) {
            m_player->activated() = true;
        }
    }

}

void GameScreen::updateCurrentPlayer() {
    m_player->text() = m_currentPlayer->id() == 2 ? "player two" : "player one";
}