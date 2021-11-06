cmake_minimum_required(VERSION 3.20)
project(Beaglebone C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)

pkg_search_module(GATTLIB REQUIRED gattlib)
pkg_search_module(PCRE REQUIRED libpcre)
add_library(
        main_lib
        SHARED
        src/main.c
        src/cli.c
        src/blescan.c
        src/data.c)

set(SOURCE_FILES src/main.c src/cli.c src/blescan.c src/data.c include/data.h)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(Beaglebone ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(Beaglebone
        gattlib)
