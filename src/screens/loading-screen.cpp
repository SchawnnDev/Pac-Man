#include "screens/loading-screen.h"

#include <utility>

using namespace pacman;

LoadingScreen::LoadingScreen(const LoadingScreenResources &p_resources, TextResources p_textResources,
                             shared_value<int> p_credit)
        : Screen(p_textResources)
        , m_credit{std::move(p_credit)}
        , m_bonusAnimation{p_resources.bonusAnimation}
        , m_nothingSprite{p_resources.nothingSprite}
        , m_charNick{std::make_shared<Text>("character / nickname", Position{m_winMiddleX - CALC(10), 120}, m_charSize, m_spacing, p_textResources)}
        , m_blinky{std::make_shared<Text>("- shadow  \"blinky\"", Position{m_ghostX, 180}, m_charSize, m_spacing, p_textResources)}
        , m_blinkyImage{std::make_shared<Image>(p_resources.blinkyRight, Position{m_ghostX - 72, 180 - 9}, Position{36, 36})}
        , m_pinky{std::make_shared<Text>("- speedy  \"pinky\"", Position{m_ghostX, 240}, m_charSize, m_spacing, p_textResources)}
        , m_pinkyImage{std::make_shared<Image>(p_resources.pinkyRight, Position{m_ghostX - 72, 240 - 9}, Position{36, 36})}
        , m_inky{std::make_shared<Text>("- bashful \"inky\"", Position{m_ghostX, 300}, m_charSize, m_spacing, p_textResources)}
        , m_inkyImage{std::make_shared<Image>(p_resources.inkyRight, Position{m_ghostX - 72, 300 - 9}, Position{36, 36})}
        , m_clyde{std::make_shared<Text>("- pokey   \"clyde\"", Position{m_ghostX, 360}, m_charSize, m_spacing, p_textResources)}
        , m_clydeImage{std::make_shared<Image>(p_resources.clydeRight, Position{m_ghostX - 72, 360 - 9}, Position{36, 36})}
        , m_midway{std::make_shared<Text>("@ 1980 midway mfg. co.",Position{m_winMiddleX - CALC(11),WINDOW_SIZE_HEIGHT -50 - 60}, m_charSize, m_spacing, p_textResources)}
        //
        , m_pointImage{std::make_shared<Image>(p_resources.pointSprite, Position{m_winMiddleX - 102, m_scoreY + 8}, Position{5, 5})}
        , m_bonusImage{std::make_shared<Image>(m_bonusAnimation.display().value_or(p_resources.nothingSprite), Position{m_winMiddleX - 110, m_scoreY + 40}, Position{20, 20})}
        , m_score10Image{std::make_shared<Image>(p_resources.score10Sprite, Position{m_winMiddleX - 70, m_scoreY}, Position{40, 20})}
        , m_score50Image{std::make_shared<Image>(p_resources.score50Sprite, Position{m_winMiddleX - 70, m_scoreY + 40}, Position{40, 20})}
        , m_score10PtsImage{std::make_shared<Image>(p_resources.ptsSprite, Position{m_winMiddleX - 12, m_scoreY + 4}, Position{35, 15})}
        , m_score50PtsImage{std::make_shared<Image>(p_resources.ptsSprite, Position{m_winMiddleX - 12, m_scoreY + 44}, Position{35, 15})}
        // second info screen
        , m_startButton{std::make_shared<Text>("push start button", Position{m_winMiddleX - CALC(8), m_winMiddleY - 40}, m_charSize, m_spacing, p_textResources)}
        , m_players{std::make_shared<Text>("1 player only", Position{m_winMiddleX - CALC(6), m_winMiddleY + 60}, m_charSize, m_spacing, p_textResources)}
        , m_bonusPacman{std::make_shared<Text>("bonus pac-man for 10000 ", Position{m_winMiddleX - CALC(11) - 17, m_winMiddleY + 160}, m_charSize, m_spacing, p_textResources)}
        , m_bonusPacmanPtsImage{std::make_shared<Image>(p_resources.ptsSprite, Position{m_winMiddleX + CALC(12), m_bonusPacman->position().y() + 4}, Position{35, 15})}
{
    m_blinky->color() = {216, 40, 0};
    m_pinky->color() = {252, 196, 216};
    m_inky->color() = {0, 232, 216};
    m_clyde->color() = {252, 152, 56};
    m_midway->color() = {187, 142, 179};
    m_players->color() = {0,255,255};
    m_startButton->color() = {255, 184, 81};
    m_bonusPacman->color() = {255, 184, 174};
    m_bonusPacmanPtsImage->color() = {255, 184, 174};
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
    addElement(m_charNick);
    addElement(m_startButton);
    addElement(m_players);
    addElement(m_bonusPacman);
    addElement(m_bonusPacmanPtsImage);
    LoadingScreen::reset();
}


void LoadingScreen::tick() noexcept {
    if(!activated()) return;

    if(m_credit != 0)
        return;

    ticks()++;

    auto found = false;
    auto els = elements();
    const auto size = els.size() - 4; // 3 > reserved

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
    m_charNick->activated() = true;
    m_startButton->activated() = false;
    m_players->activated() = false;
    m_bonusPacman->activated() = false;
    m_bonusPacmanPtsImage->activated() = false;
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

void LoadingScreen::updateCredit() noexcept
{
    if(m_credit > 0)
    {
        disable();
        m_charNick->activated() = false;
        m_startButton->activated() = true;
        m_players->activated() = true;
        m_bonusPacman->activated() = true;
        m_bonusPacmanPtsImage->activated() = true;
        m_midway->activated() = true;
        m_players->text() = m_credit == 1 ? "1 player only" : "1 or 2 players";
    } else {
        reset();
    }
}

