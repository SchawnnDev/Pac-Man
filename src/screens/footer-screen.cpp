#include "screens/footer-screen.h"

using namespace pacman;

FooterScreen::FooterScreen(TextResources p_textResources, shared_value<int> p_credit)
    : Screen(p_textResources)
        , m_credit{std::move(p_credit)}
        , m_creditText{std::make_shared<Text>("credit  0", Position{25, WINDOW_SIZE_HEIGHT - 25}, m_charSize, m_spacing, p_textResources)}
{
    addElement(m_creditText);
    reset();
}


void FooterScreen::tick() noexcept
{
    if(!activated()) return;
    //todo:
}

void FooterScreen::reset() noexcept
{
    m_creditText->activated() = true;
}

void FooterScreen::updateCredit() noexcept
{
    m_creditText->text() = "credit  " + std::to_string(m_credit);
}

void FooterScreen::updateState() noexcept
{
    // TODO:
    m_creditText->activated() = false;
}
