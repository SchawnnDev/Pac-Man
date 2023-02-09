#pragma once

#include "constants.h"
#include <SDL_rect.h>

inline SDL_Rect getPosition(int x, int y)
{
    return {x * BOARD_CASE_SIZE_WIDTH, y * BOARD_CASE_SIZE_HEIGHT};
}

inline SDL_Rect getCenteredPosition(int x, int y)
{
    SDL_Rect pos = getPosition(x, y);
    pos.x += BOARD_CASE_SIZE_WIDTH / 2;
    pos.y += BOARD_CASE_SIZE_HEIGHT / 2;
    return pos;
}