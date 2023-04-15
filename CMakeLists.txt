cmake_minimum_required(VERSION 3.8)

project(PacMan LANGUAGES CXX)

# add dependencies
include(cmake/CPM.cmake)

SET(BUILD_SHARED_LIBS OFF CACHE BOOL "BUILD_SHARED_LIBS" FORCE)
SET(BUILD_STATIC_LIBS ON CACHE BOOL "BUILD_STATIC_LIBS" FORCE)
SET(POSITION_INDEPENDENT_CODE ON CACHE BOOL "POSITION_INDEPENDENT_CODE" FORCE)

string(TIMESTAMP BEFORE "%s")
CPMAddPackage(
        NAME SDL2
        GITHUB_REPOSITORY libsdl-org/SDL
        GIT_TAG release-2.26.2
        OPTIONS
        "SDL2_DISABLE_INSTALL ON"
        "SDL_SHARED OFF"
        "SDL_STATIC ON"
        "SDL_STATIC_PIC ON"
        "SDL_WERROR OFF"
)
find_package(SDL2 REQUIRED)
if (SDL2_ADDED)
    file(GLOB SDL_HEADERS "${SDL_SOURCE_DIR}/include/*.h")

    # Create a target that copies headers at build time, when they change
    add_custom_target(sdl_copy_headers_in_build_dir
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${SDL_SOURCE_DIR}/include" "${CMAKE_BINARY_DIR}/SDLHeaders/SDL2"
            DEPENDS ${SDL_HEADERS})

    # Make SDL depend from it
    add_dependencies(SDL2-static sdl_copy_headers_in_build_dir)

    # And add the directory where headers have been copied as an interface include dir
    target_include_directories(SDL2-static INTERFACE "${CMAKE_BINARY_DIR}/SDLHeaders")

    set(SDL2_INCLUDE_DIR ${SDL2_SOURCE_DIR}/include)
endif()
string(TIMESTAMP AFTER "%s")
math(EXPR DELTASDL "${AFTER} - ${BEFORE}")
message(STATUS "SDL2 TIME: ${DELTASDL}s")

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
        include/entities/ghost.h
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
        include/game/game-cycle.h
        include/audio/audio-handler.h
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
        src/screens/screen.cpp
        src/screens/elements/text.cpp
        src/screens/loading-screen.cpp
        src/screens/elements/image.cpp
        src/screens/footer-screen.cpp
        src/screens/header-screen.cpp
        src/screens/game-screen.cpp
        src/audio/audio-handler.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR} ${SDL_Mixer_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} SDL2-static pugixml::pugixml SDL2_mixer)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

IF (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
ENDIF ()
