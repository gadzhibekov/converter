cmake_minimum_required(VERSION 3.16)

project(cc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    Network
)

find_package(Boost REQUIRED)

set(SOURCES
    src/main.cpp
    src/utils.cpp
    src/main_window.cpp
    src/label.cpp
    src/button.cpp
    src/text_editor.cpp
    src/save_dir_window.cpp
    src/line_edit.cpp
    src/settings_window.cpp
    src/settings_window_items.cpp
    src/theme.cpp
    src/message_box.cpp
    src/layout.cpp
)

set(HEADERS
    src/utils.h
    src/main_window.h
    src/label.h
    src/button.h
    src/text_editor.h
    src/save_dir_window.h
    src/line_edit.h
    src/settings_window.h
    src/settings_window_items.h
    src/theme.h
    src/message_box.h
    src/layout.h
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Widgets
    Qt::Network
    pthread
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(APPDIR "$ENV{PWD}/AppDir")
install(CODE "
    message(STATUS \"AppDir path: ${APPDIR}\")
")