// CMakeLists.txt - Файл для сборки проекта с CMake
cmake_minimum_required(VERSION 3.14)
project(VueQtApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Widgets WebEngine WebEngineWidgets REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    backend.h
    backend.cpp
    resources.qrc
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::WebEngine
    Qt5::WebEngineWidgets
)

# Копируем файлы Vue.js в директорию с бинарником
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/frontend/dist
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/frontend/dist
)