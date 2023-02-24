cmake_minimum_required(VERSION 3.21)
project(search_engine)

set(JSON_BuildTests OFF CACHE INTERNAL "")
include(FetchContent)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)


add_executable(search_engine main.cpp ConverterJSON.cpp ${MY_INCLUDE_DIR}/ConverterJSON.h InvertedIndex.cpp ${MY_INCLUDE_DIR}/InvertedIndex.h SearchEngine.cpp ${MY_INCLUDE_DIR}/SearchEngine.h ${MY_INCLUDE_DIR}/gui.h ${MY_INCLUDE_DIR}/callermain.h)



target_link_libraries(search_engine
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        nlohmann_json::nlohmann_json)

target_include_directories(search_engine PUBLIC ${MY_INCLUDE_DIR})


if (WIN32)
    set(DEBUG_SUFFIX)

    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
