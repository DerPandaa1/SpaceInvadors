# boilerplate
cmake_minimum_required (VERSION 3.15)

# set project name
project (SpaceInvadors)

# Dependencies
set(RAYLIB_VERSION 4.2.0)
# See if raylib was installed...
find_package(raylib ${RAYLIB_VERSION} QUIET)

if(NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    # If raylib was not found, download its source and build it
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        # Do not build raylibs' examples
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Our project
add_executable(${PROJECT_NAME} main.c)
# Link raylib into binary
target_link_libraries(${PROJECT_NAME} raylib)
# Link math into binary
target_link_libraries(${PROJECT_NAME} m)

# include local pthread dll if on Windows
if (WIN32)
    target_link_libraries(${PROJECT_NAME} "-l./libwinpthread-1.dll")
endif()

# Link required frameworks on MacOS
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()