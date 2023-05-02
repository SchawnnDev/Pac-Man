#include <utility>

#include "screens/header-screen.h"

using namespace pacman;

HeaderScreen::HeaderScreen(TextResources p_textResources, shared_value<int> const& p_highScore, shared_value<int> const& p_playerCount, PlayerPtr&p_currentPlayer)
        : Screen(p_textResources)
        , m_highScore{p_highScore}
        , m_currentPlayer{p_currentPlayer}
        , m_playerCount{p_playerCount}
        , m_oneUp{std::make_shared<Text>("1up", Position{25 + strTextSize(2, m_charSize, m_spacing), 5}, m_charSize, m_spacing, p_textResources)}
        , m_highScoreTitle{std::make_shared<Text>("high score", Position{m_winMiddleX - strTextSize(5, m_charSize, m_spacing), 5}, m_charSize, m_spacing, p_textResources)}
        , m_twoUp{std::make_shared<Text>("2up", Position{WINDOW_SIZE_WIDTH - 2 * m_oneUp->textSize() - 25, 5}, m_charSize, m_spacing, p_textResources)}
        , m_score1up{std::make_shared<Text>("00", Position{25 + strTextSize(4, m_charSize, m_spacing), 29}, m_charSize, m_spacing, p_textResources)}
        , m_score2up{std::make_shared<Text>("00", Position{WINDOW_SIZE_WIDTH - 2 * m_oneUp->textSize() - 25 + strTextSize(2, m_charSize, m_spacing), 29}, m_charSize, m_spacing, p_textResources)}
        , m_highScoreText{std::make_shared<Text>("00", Position{m_winMiddleX + strTextSize(2, m_charSize, m_spacing), 29}, m_charSize, m_spacing, p_textResources)}
{
    addElement(m_oneUp);
    addElement(m_twoUp);
    addElement(m_highScoreTitle);
    addElement(m_score1up);
    addElement(m_score2up);
    addElement(m_highScoreText);
    HeaderScreen::reset();
}

void HeaderScreen::tick()
{
    if (!activated() || m_currentPlayer->id() == -1) return;

    if (ticks() >= 20)
    {
        if (m_currentPlayer->id() == 1)
        {
            m_oneUp->activated() = !m_oneUp->activated();
            m_twoUp->activated() = m_playerCount > 1;
        } else
        {
            m_oneUp->activated() = true;
            m_twoUp->activated() = !m_twoUp->activated();
        }

        ticks() = 0;
    }

    ticks()++;
}

void HeaderScreen::reset()
{
    m_oneUp->activated() = true;
    m_twoUp->activated() = true;
    m_highScoreTitle->activated() = true;
    m_score1up->activated() = true;
    m_score2up->activated() = true;
    m_oneUp->activated() = true;
    m_twoUp->activated() = true;
    m_highScoreText->activated() = m_highScore != 0;
    ticks() = 0;
}

void HeaderScreen::updateHighScore()
{
    m_highScoreText->text() = std::to_string(m_highScore);
    // Handle new position (when text gets greater, moved from one char x size)
    auto x = m_winMiddleX + strTextSize(2, m_charSize, m_spacing);
    auto strlen = m_highScoreText->text().length();

    if(strlen > 2)
        x -= strTextSize(static_cast<int>(strlen) - 2, m_charSize, m_spacing);

    m_highScoreText->position().x() = x;
    m_highScoreText->activated() = m_highScore > 0;
}

void HeaderScreen::updateScore(int p_playerId)
{
    auto const score = m_currentPlayer->score();
    (p_playerId == 2 ? m_score2up : m_score1up)->text() = score == 0 ? "00" : std::to_string(m_currentPlayer->score());

    // Handle new position (when text gets greater, moved from one char x size)
    auto x = p_playerId == 2 ? WINDOW_SIZE_WIDTH - 2*m_oneUp->textSize() - 25 + strTextSize(2, m_charSize, m_spacing) : 25 + strTextSize(4, m_charSize, m_spacing);
    auto strlen = (p_playerId == 2 ? m_score2up : m_score1up)->text().length();

    if(strlen > 2)
        x -= strTextSize(static_cast<int>(strlen) - 2, m_charSize, m_spacing);

    (p_playerId == 2 ? m_score2up : m_score1up)->position().x() = x;
}

void HeaderScreen::updatePlayerCount()
{
    auto const isMultiplayer = m_playerCount > 1;
    m_twoUp->activated() = isMultiplayer;
    m_score2up->activated() = isMultiplayer;
}

