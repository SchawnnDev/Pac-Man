cmake_minimum_required(VERSION 3.8)

project(PacMan LANGUAGES CXX)

# add dependencies
include(cmake/CPM.cmake)

find_package(SDL2 REQUIRED)

# XML Reader Library
CPMAddPackage("gh:zeux/pugixml#v1.13")

add_executable(${PROJECT_NAME} ""
        include/entities/entity.h
        include/entities/pacman.h
        include/sprite.h
        include/sprite-animation.h
        include/sprite-handler.h
        include/utils/constants.h
        include/board/board.h
        include/board/board-case.h
        include/utils/position.h
        include/entities/ghosts/ghost.h
        include/entities/ghosts/blinky.h
        include/game.h
        include/sprite-animation-structs.h

        src/sprite.cpp
        src/sprite-handler.cpp
        src/sprite-animation.cpp
        src/entities/pacman.cpp
        src/entities/entity.cpp
        src/board/board.cpp
        src/board/board-case.cpp
        src/entities/ghosts/ghost.cpp
        src/entities/ghosts/blinky.cpp
        src/utils/position.cpp
        src/game.cpp
        include/utils/utils.h
        include/board/text.h
        src/entities/ghosts/clyde.cpp
        include/entities/ghosts/clyde.h
        include/entities/ghosts/inky.h
        include/entities/ghosts/pinky.h
        src/entities/ghosts/inky.cpp src/entities/ghosts/pinky.cpp include/utils/clock.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} pugixml::pugixml)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

IF (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
ENDIF ()
