#include <utility>

#include "screens/header-screen.h"

using namespace pacman;

HeaderScreen::HeaderScreen(TextResources p_textResources, shared_value<int> p_highScore,
                           shared_value<int> p_currentPlayer, std::array<shared_value<int>, 2> p_scores)
        : Screen(p_textResources)
        , m_highScore{std::move(p_highScore)}
        , m_currentPlayer{std::move(p_currentPlayer)}
        , m_scores{std::move(p_scores)}
        , m_oneUp{std::make_shared<Text>("1up", Position{25, 5}, m_charSize, m_spacing, p_textResources)}
        , m_highScoreTitle{std::make_shared<Text>("high score", Position{m_winMiddleX - strTextSize(5, m_charSize, m_spacing), 5}, m_charSize, m_spacing, p_textResources)}
        , m_twoUp{std::make_shared<Text>("2up", Position{WINDOW_SIZE_WIDTH - m_oneUp->textSize() - 25, 5}, m_charSize, m_spacing, p_textResources)}
        , m_score{std::make_shared<Text>("00", Position{25 + strTextSize(2, m_charSize, m_spacing), 29}, m_charSize, m_spacing, p_textResources)}
        , m_highScoreText{std::make_shared<Text>("00", Position{m_winMiddleX + strTextSize(2, m_charSize, m_spacing), 29}, m_charSize, m_spacing, p_textResources)}
{
    addElement(m_oneUp);
    addElement(m_twoUp);
    addElement(m_highScoreTitle);
    addElement(m_score);
    addElement(m_highScoreText);
    HeaderScreen::reset();
}

void HeaderScreen::tick() noexcept
{
    if (!activated() || m_currentPlayer == -1) return;
    // Display only 1up if single player
    if(m_currentPlayer == 0 && m_twoUp->activated())
    {
        m_twoUp->activated() = false;
    }

    if(m_highScore > 0 && !m_highScoreText->activated()) {
        m_highScoreText->activated() = true;
    }

    if (ticks() >= 20)
    {
        if (m_currentPlayer == 0)
        {
            m_oneUp->activated() = !m_oneUp->activated();
        } else
        {
            m_twoUp->activated() = !m_twoUp->activated();
        }

        ticks() = 0;
    }

    ticks()++;
}

void HeaderScreen::reset() noexcept
{
    m_oneUp->activated() = true;
    m_twoUp->activated() = true;
    m_highScoreTitle->activated() = true;
    m_score->activated() = true;
    m_oneUp->activated() = true;
    m_twoUp->activated() = true;
    m_highScoreText->activated() = false;
    ticks() = 0;
}

void HeaderScreen::updateHighScore() noexcept
{
    m_highScoreText->text() = std::to_string(m_highScore);
    // Handle new position (when text gets greater, moved from one char x size)
    auto x = m_winMiddleX + strTextSize(2, m_charSize, m_spacing);
    auto strlen = m_highScoreText->text().length();

    if(strlen > 2)
        x -= strTextSize(strlen - 2, m_charSize, m_spacing);

    m_highScoreText->position().x() = x;
}
