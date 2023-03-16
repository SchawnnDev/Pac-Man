#include "screens/footer-screen.h"
#include "entities/fruit.h"

#include <utility>

using namespace pacman;

FooterScreen::FooterScreen(TextResources p_textResources, shared_value<int> p_credit,
                           shared_value<GameState> p_gameState,
                           std::array<shared_value<int>, 2> const &p_levels,
                           std::array<shared_value<int>, 2> const &p_lives,
                           const FooterScreenResources& p_footerResources)
    : Screen(p_textResources)
        , m_credit{std::move(p_credit)}
        , m_gameState{std::move(p_gameState)}
        , m_levels{p_levels}
        , m_lives{p_lives}
        , m_creditText{std::make_shared<Text>("credit  0", Position{25, WINDOW_SIZE_HEIGHT - 25}, m_charSize, m_spacing, p_textResources)}
        , m_fruits{}
        , m_livesImages{}
        , m_footerResources{p_footerResources}
{
    addElement(m_creditText);

    auto const lifeSize = Position{BOARD_CASE_SIZE_WIDTH, BOARD_CASE_SIZE_HEIGHT};
    auto const lifePosition = Position{2 * lifeSize.x(), WINDOW_SIZE_HEIGHT - 46};
    for (int i = 0; i < 3; ++i) {
        m_livesImages[i] = std::make_shared<Image>(p_footerResources.lifeSprite, lifePosition.add({i*(32+16),0}), lifeSize);
        addElement(m_livesImages[i]);
    }
    auto const levelSize = Position{BOARD_CASE_SIZE_WIDTH, BOARD_CASE_SIZE_HEIGHT};
    auto const levelsPosition = Position{WINDOW_SIZE_WIDTH - (3 * levelSize.x()), WINDOW_SIZE_HEIGHT - 46};
    for (int i = 0; i < FRUITS_DISPLAYED; ++i) {
        m_fruits[i] = std::make_shared<Image>(p_footerResources.lifeSprite, levelsPosition.subtract({i * (32 + 16), 0}), levelSize);
        addElement(m_fruits[i]);
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
    for (auto &level: m_fruits)
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
    auto const fruits = Fruit::getFruitsByLevel(m_levels[m_currentPlayer]);
    for (int i = 0; i < FRUITS_DISPLAYED; ++i)
    {
        auto const fruit = fruits[i];
        auto const& level = m_fruits[i];
        if(fruit == -1) {
            level->activated() = false;
            continue;
        }
        level->activated() = true;
        level->sprite() = m_footerResources.fruitsSprites[i];
    }
}