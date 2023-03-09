#pragma once

#include <cstddef>

constinit const int WINDOW_SIZE_WIDTH = 672;
constinit const int WINDOW_SIZE_HEIGHT = 1004;
constinit const int BOARD_SIZE_X = 21;
constinit const int BOARD_SIZE_Y = 27;
constinit const int BOARD_SIZE_WIDTH = 672;
constinit const int BOARD_SIZE_HEIGHT = 864;
constinit const int BOARD_OFFSET_Y = 84;
constinit const int BOARD_CASE_SIZE_WIDTH = (BOARD_SIZE_WIDTH / BOARD_SIZE_X);
constinit const int BOARD_CASE_SIZE_HEIGHT = (BOARD_SIZE_HEIGHT / BOARD_SIZE_Y);
constinit const int FRAMERATE = 60;

// CASE FLAGS
constinit const int CASE_FLAG_NO_UP = 1 << 0;
constinit const int CASE_FLAG_TUNNEL_SLOW_DOWN = 1 << 1;

// 930 -> 864
// 90 -> 84
// 60 -> 56