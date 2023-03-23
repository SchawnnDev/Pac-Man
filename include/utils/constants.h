#pragma once

#include <cstddef>
#include <array>

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
constinit const int DOTS_TO_EAT = 198; // Normally 244

// CASE FLAGS
constinit const int CASE_FLAG_NO_UP = 1 << 0;
constinit const int CASE_FLAG_TUNNEL_SLOW_DOWN = 1 << 1;

// TIMEOUTS
constinit const int COUNTER_BLA = 180;

// FRUITS
constinit const int FRUITS_REGISTERED = 14;
constinit const std::array<int, FRUITS_REGISTERED> FRUITS_LEVELS {0,1,2,2,3,3,4,4,5,5,6,6,7,7};
constinit const int FRUITS_DISPLAYED = 7;
constinit const int DOTS_TO_EAT_FIRST_FRUIT = 57; // Normally 70
constinit const int DOTS_TO_EAT_SECOND_FRUIT = 122; // Normally 150
constinit const std::array<int, FRUITS_REGISTERED> FRUIT_VALUES{100, 300, 500, 500, 700, 700, 1000, 1000, 2000,
                                                                      2000, 3000, 3000, 5000, 5000};