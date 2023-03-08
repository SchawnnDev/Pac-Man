#pragma once

#include "screen.h"
#include "image.h"
#include "utils/shared_value.h"

#include <utility>

namespace pacman {

    class LoadingScreen : public Screen {
        const int m_charSize = 20;
        const int m_spacing = 3;
        const int m_ghostMiddleX = WINDOW_SIZE_WIDTH / 2 - strTextSize("- shadow ", m_charSize, m_spacing);
        const int m_scoreMiddleY = WINDOW_SIZE_HEIGHT / 4 * 3 - 40;
        SpriteAnimation m_bonusAnimation;
        Sprite m_nothingSprite;

        // Texts
        TextElement m_oneUp;
        TextElement m_highScore;
        TextElement m_twoUp;
        TextElement m_score;
        TextElement m_charNick;
        TextElement m_blinky;
        TextElement m_pinky;
        TextElement m_inky;
        TextElement m_clyde;
        TextElement m_midway;
        TextElement m_creditText;

        // Images
        ImageElement m_blinkyImage;
        ImageElement m_pinkyImage;
        ImageElement m_inkyImage;
        ImageElement m_clydeImage;
        ImageElement m_score10Image;
        ImageElement m_score50Image;
        ImageElement m_score10PtsImage;
        ImageElement m_score50PtsImage;
        ImageElement m_pointImage;
        ImageElement m_bonusImage;

        shared_value<int> m_credit;
        int oldCredit;
    public:

        LoadingScreen(const LoadingScreenResources& p_loadingScreenResources, TextResources p_textResources, shared_value<int> p_credit);

        void tick() noexcept override;
        void reset() noexcept override;
        void disable() noexcept;

        [[nodiscard]] TextElement const& credit() { return m_creditText; }

    };

}