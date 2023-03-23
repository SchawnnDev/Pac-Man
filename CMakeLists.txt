cmake_minimum_required(VERSION 3.8)

project(PacMan LANGUAGES CXX)

# add dependencies
include(cmake/CPM.cmake)

find_package(SDL2 REQUIRED)

# XML Reader Library
CPMAddPackage("gh:zeux/pugixml#v1.13")

# Add SDL Mixer
string(TIMESTAMP BEFORE "%s")
CPMAddPackage(
        GITHUB_REPOSITORY libsdl-org/SDL_Mixer
        GIT_TAG release-2.6.3
        OPTIONS
        "SDL2MIXER_INSTALL OFF"
        "SDL2MIXER_SAMPLES OFF"
        "SDL2MIXER_VENDORED ON"
        "SDL2MIXER_BUILD_SHARED_LIBS OFF"
        "SDL2MIXER_OPUS OFF"
        "SDL2MIXER_OGG OFF"
        "SDL2MIXER_MIDI OFF"
        "SDL2MIXER_MP3 OFF"
        "SDL2MIXER_VORBIS OFF"
        "SDL2MIXER_MOD OFF"
        "SDL2MIXER_FLAC OFF"
)
find_package(SDL_Mixer REQUIRED)
string(TIMESTAMP AFTER "%s")
math(EXPR DELTASDL_Mixer "${AFTER} - ${BEFORE}")
message(STATUS "SDL_Mixer TIME: ${DELTASDL_Mixer}s")

add_executable(${PROJECT_NAME} ""
        include/entities/entity.h
        include/entities/pacman.h
        include/entities/ghosts/clyde.h
        include/entities/ghosts/inky.h
        include/entities/ghosts/pinky.h
        include/entities/ghosts/ghost.h
        include/entities/ghosts/blinky.h
        include/entities/fruit.h
        include/sprites/sprite.h
        include/sprites/sprite-animation.h
        include/sprites/sprite-handler.h
        include/sprites/sprite-resources-structs.h
        include/board/board.h
        include/board/board-case.h
        include/screens/elements/text.h
        include/screens/loading-screen.h
        include/screens/screen.h
        include/screens/drawable.h
        include/screens/elements/image.h
        include/screens/header-screen.h
        include/screens/footer-screen.h
        include/screens/game-screen.h
        include/game/game.h
        include/game/level.h
        include/game/game-state.h
        include/game/player.h
        include/utils/random.h
        include/utils/shared_value.h
        include/utils/constants.h
        include/utils/position.h
        include/utils/utils.h
        include/utils/clock.h

        src/sprites/sprite.cpp
        src/sprites/sprite-handler.cpp
        src/sprites/sprite-animation.cpp
        src/board/board.cpp
        src/board/board-case.cpp
        src/game/game.cpp
        src/entities/entity.cpp
        src/entities/pacman.cpp
        src/entities/fruit.cpp
        src/entities/ghosts/ghost.cpp
        src/entities/ghosts/blinky.cpp
        src/entities/ghosts/clyde.cpp
        src/entities/ghosts/inky.cpp
        src/entities/ghosts/pinky.cpp
        src/screens/screen.cpp
        src/screens/elements/text.cpp
        src/screens/loading-screen.cpp
        src/screens/elements/image.cpp
        src/screens/footer-screen.cpp
        src/screens/header-screen.cpp
        src/screens/game-screen.cpp
        src/utils/position.cpp
        )

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL_Mixer_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} pugixml::pugixml SDL2_mixer)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

IF (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
ENDIF ()
