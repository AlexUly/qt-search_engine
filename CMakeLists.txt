cmake_minimum_required(VERSION 3.21)
project(search_engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "F:/Torrent/5.15.2/mingw81_64/lib/cmake")
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
enable_testing()
add_subdirectory(src)
add_subdirectory(tests)





