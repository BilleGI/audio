cmake_minimum_required(VERSION 3.22)

project("Audioplayer" VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core Widgets Multimedia MultimediaWidgets REQUIRED)

add_executable(audio main.cpp)

target_link_libraries(audio PRIVATE Qt6::Core Qt6::Widgets Qt6::Multimedia Qt6::MultimediaWidgets)

set_target_properties(audio PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSx_BUNDLE ON
)

install(TARGETS audio
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
