#include "screens/footer-screen.h"

#include <utility>

using namespace pacman;

FooterScreen::FooterScreen(TextResources p_textResources, shared_value<int> p_credit,
                           shared_value<GameState> p_gameState, shared_value<int> p_level,
                           std::array<shared_value<int>, 2> const &p_lives,
                           const FooterScreenResources& p_footerResources)
    : Screen(p_textResources)
        , m_credit{std::move(p_credit)}
        , m_gameState{std::move(p_gameState)}
        , m_level{std::move(p_level)}
        , m_lives{p_lives}
        , m_creditText{std::make_shared<Text>("credit  0", Position{25, WINDOW_SIZE_HEIGHT - 25}, m_charSize, m_spacing, p_textResources)}
        , m_levels{}
        , m_livesImages{}
{
    addElement(m_creditText);

    for (int i = 0; i < 3; ++i) {
        m_livesImages[i] = std::make_shared<Image>(p_footerResources.lifeSprite, Position{25 + 32 * i, WINDOW_SIZE_HEIGHT - 100}, Position{32,32});
        addElement(m_livesImages[i]);
    }

    for (int i = 0; i < 7; ++i) {
        m_levels[i] = std::make_shared<Image>(p_footerResources.lifeSprite, Position{WINDOW_SIZE_WIDTH - (25 + 50 * i), WINDOW_SIZE_HEIGHT - 100}, Position{32,32});
        addElement(m_levels[i]);
    }

    FooterScreen::reset();
}


void FooterScreen::tick() noexcept
{
    if(!activated()) return;
    //todo:
}

void FooterScreen::reset() noexcept
{
    m_creditText->activated() = true;

    for (auto &livesImage: m_livesImages)
        livesImage->activated() = false;
    for (auto &level: m_levels)
        level->activated() = false;
}

void FooterScreen::updateCredit() noexcept
{
    m_creditText->text() = "credit  " + std::to_string(m_credit);
}

void FooterScreen::updateState() noexcept
{
    m_creditText->activated() = m_gameState == GameState::LoadingScreen;

    updateLives();
    updateLevels();

}

void FooterScreen::updateLives() noexcept
{
    auto const playing = m_gameState == GameState::Playing;
    auto const lives = m_lives[m_currentPlayer];

    for (int i = 0; i < m_livesImages.size(); ++i)
        m_livesImages[i]->activated() = playing && i < lives;
}

void FooterScreen::updateLevels() noexcept
{
    auto const playing = m_gameState == GameState::Playing;

/*    for (int i = 0; i < m_level && i < 7; ++i)
        m_livesImages[i]->activated() = playing && i < lives;*/
// todo: handle fruits
}