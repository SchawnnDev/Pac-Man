#include "screens/footer-screen.h"

using namespace pacman;

void FooterScreen::tick() noexcept
{
    if(!activated()) return;

}

void FooterScreen::reset() noexcept
{

}

FooterScreen::FooterScreen(TextResources p_textResources)
    : Screen(p_textResources)
    {}
