#include "screens/loading-screen.h"

#include <utility>

using namespace pacman;

LoadingScreen::LoadingScreen(const LoadingScreenResources &p_loadingScreenResources, TextResources p_textResources, shared_value<int> p_credit)
        : Screen(p_textResources)
        , m_credit{std::move(p_credit)}
        , oldCredit{0}
        , m_bonusAnimation{p_loadingScreenResources.bonusAnimation}
        , m_nothingSprite{p_loadingScreenResources.nothingSprite}
        , m_oneUp{std::make_shared<Text>("1up", Position{25, 5}, m_charSize, m_spacing, p_textResources)}
        , m_highScore{std::make_shared<Text>("high score",
                                       Position{WINDOW_SIZE_WIDTH / 2 - strTextSize("high ", m_charSize, m_spacing), 5},
                                       m_charSize, m_spacing, p_textResources)}
        , m_twoUp{std::make_shared<Text>("2up", Position{WINDOW_SIZE_WIDTH - m_oneUp->textSize() - 25, 5}, m_charSize,
                                         m_spacing, p_textResources)}
        , m_score{std::make_shared<Text>("00", Position{25 + strTextSize("1u", m_charSize, m_spacing), 29}, m_charSize,
                                         m_spacing, p_textResources)}
        , m_charNick{std::make_shared<Text>("character / nickname", Position{WINDOW_SIZE_WIDTH / 2 - strTextSize("character ", m_charSize, m_spacing), 120}, m_charSize,m_spacing, p_textResources)}
        , m_blinky{std::make_shared<Text>("- shadow  \"blinky\"", Position{m_ghostMiddleX, 180}, m_charSize, m_spacing,p_textResources)}
        , m_blinkyImage{std::make_shared<Image>(p_loadingScreenResources.blinkyRight, Position{m_ghostMiddleX - 72, 180 - 9},Position{36, 36})}
        , m_pinky{std::make_shared<Text>("- speedy  \"pinky\"", Position{m_ghostMiddleX, 240}, m_charSize, m_spacing,p_textResources)}
        , m_pinkyImage{std::make_shared<Image>(p_loadingScreenResources.pinkyRight, Position{m_ghostMiddleX - 72, 240 - 9},Position{36, 36})}
        , m_inky{std::make_shared<Text>("- bashful \"inky\"", Position{m_ghostMiddleX, 300}, m_charSize, m_spacing,p_textResources)}
        , m_inkyImage{std::make_shared<Image>(p_loadingScreenResources.inkyRight, Position{m_ghostMiddleX - 72, 300 - 9},Position{36, 36})}
        , m_clyde{std::make_shared<Text>("- pokey   \"clyde\"", Position{m_ghostMiddleX, 360}, m_charSize, m_spacing,p_textResources)}
        , m_clydeImage{std::make_shared<Image>(p_loadingScreenResources.clydeRight, Position{m_ghostMiddleX - 72, 360 - 9},Position{36, 36})}
        , m_midway{std::make_shared<Text>("@ 1980 midway mfg. co.",Position{WINDOW_SIZE_WIDTH / 2 - strTextSize("@ 1980 midw",m_charSize,m_spacing),WINDOW_SIZE_HEIGHT -50 - 60},m_charSize, m_spacing,p_textResources)}
        , m_creditText{std::make_shared<Text>("credit  0", Position{25, WINDOW_SIZE_HEIGHT - 25}, m_charSize, m_spacing, p_textResources)}
        //
        , m_pointImage{std::make_shared<Image>(p_loadingScreenResources.pointSprite,Position{WINDOW_SIZE_WIDTH / 2 - 102, m_scoreMiddleY + 8},Position{5, 5})}
        , m_bonusImage{std::make_shared<Image>(m_bonusAnimation.display().value_or(p_loadingScreenResources.nothingSprite),Position{WINDOW_SIZE_WIDTH / 2 - 110, m_scoreMiddleY + 40}, Position{20, 20})}
        , m_score10Image{std::make_shared<Image>(p_loadingScreenResources.score10Sprite,Position{WINDOW_SIZE_WIDTH / 2 - 70, m_scoreMiddleY},Position{40, 20})}
        , m_score50Image{std::make_shared<Image>(p_loadingScreenResources.score50Sprite,Position{WINDOW_SIZE_WIDTH / 2 - 70, m_scoreMiddleY + 40}, Position{40, 20})}
        , m_score10PtsImage{std::make_shared<Image>(p_loadingScreenResources.ptsSprite,Position{WINDOW_SIZE_WIDTH / 2 - 12, m_scoreMiddleY + 4},Position{35, 15})}
        , m_score50PtsImage{std::make_shared<Image>(p_loadingScreenResources.ptsSprite,Position{WINDOW_SIZE_WIDTH / 2 - 12, m_scoreMiddleY + 44}, Position{35, 15})}
{
    m_blinky->color() = {216, 40, 0};
    m_pinky->color() = {252, 196, 216};
    m_inky->color() = {0, 232, 216};
    m_clyde->color() = {252, 152, 56};
    m_midway->color() = {187, 142, 179};
    addElement(m_creditText);
    addElement(m_blinkyImage);
    addElement(m_blinky);
    addElement(m_pinkyImage);
    addElement(m_pinky);
    addElement(m_inkyImage);
    addElement(m_inky);
    addElement(m_clydeImage);
    addElement(m_clyde);
    addElement(m_pointImage);
    addElement(m_score10Image);
    addElement(m_score10PtsImage);
    addElement(m_bonusImage);
    addElement(m_score50Image);
    addElement(m_score50PtsImage);
    addElement(m_midway);
    addElement(m_oneUp);
    addElement(m_twoUp);
    addElement(m_highScore);
    addElement(m_score);
    addElement(m_charNick);
    LoadingScreen::reset();
}


void LoadingScreen::tick() noexcept {
    if(!activated()) return;
    ticks()++;

    // changing state
    if(m_credit != oldCredit)
    {

        if(m_credit > 0)
        {
            disable();
        } else {
            reset();
        }

    }

    oldCredit = m_credit;

    if(m_credit != 0)
    {
        return;
    }

    auto found = false;
    auto els = elements();
    const auto size = els.size();

    for (int j = 0; j < size; ++j) {
        auto &element = els[j];
        if (element->activated() || ticks() != j * (FRAMERATE / 2)) continue;
        element->activated() = true;
        found = true;
        break;
    }

    if(!found)
    {
        if (ticks() > size * (FRAMERATE / 2)) {
            if (ticks() < FRAMERATE * 1000) {
                ticks() = FRAMERATE * 1000;
            } else if (ticks() > FRAMERATE * 1005) {
                reset();
            }
        }
    }

    m_bonusImage->sprite() = m_bonusAnimation.display().value_or(m_nothingSprite);
}

void LoadingScreen::reset() noexcept {
    ticks() = 0;
    m_creditText->activated() = true;
    m_oneUp->activated() = true;
    m_twoUp->activated() = true;
    m_highScore->activated() = true;
    m_score->activated() = true;
    m_charNick->activated() = true;
    disable();
}

void LoadingScreen::disable() noexcept {
    m_blinky->activated() = false;
    m_blinkyImage->activated() = false;
    m_pinky->activated() = false;
    m_pinkyImage->activated() = false;
    m_inky->activated() = false;
    m_inkyImage->activated() = false;
    m_clyde->activated() = false;
    m_clydeImage->activated() = false;
    m_midway->activated() = false;
    m_score10Image->activated() = false;
    m_score50Image->activated() = false;
    m_score10PtsImage->activated() = false;
    m_score50PtsImage->activated() = false;
    m_pointImage->activated() = false;
    m_bonusImage->activated() = false;
}
