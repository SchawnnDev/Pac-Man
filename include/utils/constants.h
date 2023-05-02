#pragma once

#include <cstddef>
#include <array>
#include <string>

#define WINDOW_NAME "PacMan"
#define ASSETS_SPRITE_PATH "./assets/pacman_sprites.bmp"
#define ASSETS_SPRITES_PATH "./assets/pacman.sprites"
#define ASSETS_BOARD_PATH "./assets/board.xml"
#define AUDIO_FOLDER_PATH "./assets/wav/"
#define AUDIO_EXTENSION ".wav"

constexpr const int WINDOW_SIZE_WIDTH = 672;
constexpr const int WINDOW_SIZE_HEIGHT = 1004;
constexpr const int BOARD_SIZE_X = 21;
constexpr const int BOARD_SIZE_Y = 27;
constexpr const int BOARD_SIZE_WIDTH = 672;
constexpr const int BOARD_SIZE_HEIGHT = 864;
constexpr const int BOARD_OFFSET_Y = 84;
constexpr const int BOARD_CASE_SIZE_WIDTH = (BOARD_SIZE_WIDTH / BOARD_SIZE_X);
constexpr const int BOARD_CASE_SIZE_HEIGHT = (BOARD_SIZE_HEIGHT / BOARD_SIZE_Y);
constexpr const int FRAMERATE = 60;
constexpr const int DOTS_TO_EAT = 193; // Normally 244

// AUDIO
constexpr const int AUDIO_FREQUENCY = 96000;
constexpr const int AUDIO_CHANNELS = 4;
constexpr const int AUDIO_CHUNK_SIZE = 2048;
constexpr const int AUDIO_FILES_COUNT = 16;
constexpr const int AUDIO_MUNCH_DURATION = 79; // in MS
constexpr const std::array<const char *, AUDIO_FILES_COUNT> AUDIO_FILES{"credit", "death", "eat_fruit",
                                                                        "eat_ghost", "extend", "game_start",
                                                                        "intermission", "munch_1", "munch_2",
                                                                        "power_pellet", "retreating", "siren_1",
                                                                        "siren_2", "siren_3", "siren_4", "siren_5"};

// CASE FLAGS
constexpr const int CASE_FLAG_NO_UP = 1 << 0;
constexpr const int CASE_FLAG_TUNNEL_SLOW_DOWN = 1 << 1;

// TIMEOUTS
constexpr const int TIMEOUT_START_GAME = static_cast<int>(4.228798 * FRAMERATE) + 10; // Duration of start sound -> 4.228798
constexpr const int TIMEOUT_PRE_START_GAME = TIMEOUT_START_GAME / 2;
constexpr const int CYCLES_COUNT = 7;
constexpr const std::array<int, CYCLES_COUNT> START_CYCLES{7 * FRAMERATE, 20 * FRAMERATE, 7 * FRAMERATE, 20 * FRAMERATE,
                                                           5 * FRAMERATE, 20 * FRAMERATE, 5 * FRAMERATE};
constexpr const std::array<int, CYCLES_COUNT> MID_CYCLES{7 * FRAMERATE, 20 * FRAMERATE, 7 * FRAMERATE, 20 * FRAMERATE,
                                                         5 * FRAMERATE, 1033 * FRAMERATE, FRAMERATE / 60};
constexpr const std::array<int, CYCLES_COUNT> END_CYCLES{5 * FRAMERATE, 20 * FRAMERATE, 5 * FRAMERATE, 20 * FRAMERATE,
                                                         5 * FRAMERATE, 1037 * FRAMERATE, FRAMERATE / 60};
constexpr const int GHOST_FRIGHTENED_TIMEOUTS_COUNT = 18;
constexpr const std::array<int, GHOST_FRIGHTENED_TIMEOUTS_COUNT> GHOST_FRIGHTENED_TIMEOUTS{6 * FRAMERATE, 5 * FRAMERATE,
                                                                                           4 * FRAMERATE, 3 * FRAMERATE,
                                                                                           2 * FRAMERATE, 5 * FRAMERATE,
                                                                                           2 * FRAMERATE, 2 * FRAMERATE,
                                                                                           1, 5 * FRAMERATE,
                                                                                           2 * FRAMERATE, 1, 1,
                                                                                           3 * FRAMERATE, 1, 1, 0,
                                                                                           FRAMERATE};
constexpr const std::array<int, GHOST_FRIGHTENED_TIMEOUTS_COUNT> GHOST_FRIGHTENED_FLASHES{6, 5, 4, 3, 2, 5, 2, 2, 1, 5,
                                                                                          2, 1, 1, 3, 1, 1, 0, 1};
constexpr const int GHOST_FRIGHTENED_FLASH_DURATION = 10; // in ticks
// FRUITS
constexpr const int FRUITS_REGISTERED = 14;
constexpr const std::array<int, FRUITS_REGISTERED> FRUITS_LEVELS{0, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7};
constexpr const int FRUITS_DISPLAYED = 7;
constexpr const int DOTS_TO_EAT_FIRST_FRUIT = 55; // Normally 70
constexpr const int DOTS_TO_EAT_SECOND_FRUIT = 119; // Normally 150
constexpr const std::array<int, FRUITS_REGISTERED> FRUIT_VALUES{100, 300, 500, 500, 700, 700, 1000, 1000, 2000,
                                                                2000, 3000, 3000, 5000, 5000};