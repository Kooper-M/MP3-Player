cmake_minimum_required(VERSION 3.19)
project(MP3_Player LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)

qt_standard_project_setup()

qt_add_executable(MP3_Player
    MACOSX_BUNDLE
    Sources/main.cpp
    Sources/mainwindow.cpp
    Sources/audioHandler.cpp
    Sources/playlist.cpp
    
    Headers/mainwindow.h
    Headers/song.h
    Headers/mainwindow.ui
    Headers/audioHandler.h
    Headers/playlist.h
)

target_include_directories(MP3_Player PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Headers
)

target_link_libraries(MP3_Player
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Multimedia
)

include(GNUInstallDirs)

install(TARGETS MP3_Player
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MP3_Player
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})