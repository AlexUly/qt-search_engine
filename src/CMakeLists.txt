cmake_minimum_required(VERSION 3.21)
project(search_engine)

set(JSON_BuildTests OFF CACHE INTERNAL "")
include(FetchContent)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(search_engine main.cpp ConverterJSON.cpp ${MY_INCLUDE_DIR}/ConverterJSON.h InvertedIndex.cpp ${MY_INCLUDE_DIR}/InvertedIndex.h SearchEngine.cpp ${MY_INCLUDE_DIR}/SearchEngine.h)

target_include_directories(search_engine PUBLIC ${MY_INCLUDE_DIR})
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)