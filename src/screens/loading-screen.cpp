#include "screens/loading-screen.h"

using namespace pacman;

LoadingScreen::LoadingScreen(TextResources p_textResources)
        : Screen(std::move(p_textResources))
        , m_oneUp{std::make_shared<Text>("1 up", Position{1, 1}, 32, 5, p_textResources)}
        , m_twoUp{std::make_shared<Text>("2 up", Position{1, 1}, 32, 5, p_textResources)}
        , m_highScore{std::make_shared<Text>("highscore", Position{1, 1}, 32, 5, p_textResources)}
{
    addText(m_oneUp);
    addText(m_twoUp);
    addText(m_highScore);
    LoadingScreen::reset();
}


void LoadingScreen::tick() noexcept {

}

void LoadingScreen::reset() noexcept {
    ticks() = 0;
}