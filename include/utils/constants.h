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
constinit const int DOTS_TO_EAT = 193; // Normally 244

// CASE FLAGS
constinit const int CASE_FLAG_NO_UP = 1 << 0;
constinit const int CASE_FLAG_TUNNEL_SLOW_DOWN = 1 << 1;

// TIMEOUTS
constinit const int COUNTER_BLA = 180;
constinit const int CYCLES_COUNT = 7;
constinit const std::array<int, CYCLES_COUNT> START_CYCLES{7 * FRAMERATE, 20 * FRAMERATE, 7 * FRAMERATE, 20 * FRAMERATE,
                                                           5 * FRAMERATE, 20 * FRAMERATE, 5 * FRAMERATE};
constinit const std::array<int, CYCLES_COUNT> MID_CYCLES{7 * FRAMERATE, 20 * FRAMERATE, 7 * FRAMERATE, 20 * FRAMERATE,
                                                         5 * FRAMERATE, 1033 * FRAMERATE, FRAMERATE / 60};
constinit const std::array<int, CYCLES_COUNT> END_CYCLES{5 * FRAMERATE, 20 * FRAMERATE, 5 * FRAMERATE, 20 * FRAMERATE,
                                                         5 * FRAMERATE, 1037 * FRAMERATE, FRAMERATE / 60};


// FRUITS
constinit const int FRUITS_REGISTERED = 14;
constinit const std::array<int, FRUITS_REGISTERED> FRUITS_LEVELS {0,1,2,2,3,3,4,4,5,5,6,6,7,7};
constinit const int FRUITS_DISPLAYED = 7;
constinit const int DOTS_TO_EAT_FIRST_FRUIT = 55; // Normally 70
constinit const int DOTS_TO_EAT_SECOND_FRUIT = 119; // Normally 150
constinit const std::array<int, FRUITS_REGISTERED> FRUIT_VALUES{100, 300, 500, 500, 700, 700, 1000, 1000, 2000,
                                                                      2000, 3000, 3000, 5000, 5000};