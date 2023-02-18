cmake_minimum_required(VERSION 3.8)

project(PacMan LANGUAGES CXX)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} ""
        include/entities/entity.h
        include/entities/pacman.h
        include/sprite.h
        include/sprite-animation.h
        include/sprite-handler.h
        include/animations/pacman/pacman-dying-animation.h
        include/animations/pacman/pacman-up-animation.h
        include/animations/pacman/pacman-down-animation.h
        include/animations/pacman/pacman-left-animation.h
        include/animations/pacman/pacman-right-animation.h
        include/utils/constants.h
        include/board/board.h
        include/board/board-case.h
        include/utils/position.h
        include/animations/bonus-animation.h
        include/entities/ghosts/ghost.h
        include/entities/ghosts/blinky.h
        include/game.h

        src/sprite.cpp
        src/sprite-handler.cpp
        src/sprite-animation.cpp
        src/entities/pacman.cpp
        src/entities/entity.cpp
        src/animations/pacman/pacman-dying-animation.cpp
        src/animations/pacman/pacman-up-animation.cpp
        src/animations/pacman/pacman-down-animation.cpp
        src/animations/pacman/pacman-left-animation.cpp
        src/animations/pacman/pacman-right-animation.cpp
        src/board/board.cpp
        src/board/board-case.cpp
        src/animations/bonus-animation.cpp
        src/entities/ghosts/ghost.cpp
        src/entities/ghosts/blinky.cpp
        src/utils/position.cpp
        src/game.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )
target_sources(${PROJECT_NAME} PRIVATE src/pacman-editor.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")

# add dependencies
include(cmake/CPM.cmake)

# XML Reader Library
CPMAddPackage("gh:zeux/pugixml#v1.13")

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} pugixml::pugixml)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

IF (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
ENDIF ()
