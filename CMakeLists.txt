cmake_minimum_required(VERSION 3.8)

project(PacMan LANGUAGES CXX)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} ""
        include/entities/entity.h
        include/entities/banana.h
        include/sprite.h
        include/sprite-animation.h
        include/sprite-handler.h

        src/sprite.cpp
        src/sprite-handler.cpp src/sprite-animation.cpp src/entities/banana.cpp src/entities/entity.cpp src/animations/banana-dying-animation.cpp include/animations/banana-dying-animation.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )
target_sources(${PROJECT_NAME} PRIVATE src/pacman.cpp)
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
