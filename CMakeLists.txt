cmake_minimum_required(VERSION 3.20)
project(ben-mark-project C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

add_executable(main
    main.c
    src/load-image.c
    src/start-screen.c
        src/load-menu.c
        src/load-menu.h
)

target_compile_options(main PRIVATE -Wall -Wextra)
target_link_libraries(main PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf m)
