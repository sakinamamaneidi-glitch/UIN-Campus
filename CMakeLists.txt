cmake_minimum_required(VERSION 3.25)

project(UIN-Campus VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(uincampus_core
    src/version.cpp
    src/regles.cpp
    src/saisie.cpp
)

target_include_directories(uincampus_core PUBLIC include)

add_executable(uin-campus
    app/main.cpp
)

target_link_libraries(uin-campus PRIVATE uincampus_core)
