cmake_minimum_required(VERSION 3.10)
project(Beaglebone C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)

pkg_search_module(GATTLIB REQUIRED gattlib)
pkg_search_module(PCRE REQUIRED libpcre)
add_library(
        main_lib
        SHARED
        main.c
        cli.c
        blescan.c
        data.c)

set(SOURCE_FILES main.c cli.c blescan.c data.c)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(Beaglebone ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(Beaglebone ${GATTLIB_LIBRARIES} ${GATTLIB_LDFLAGS} ${PCRE_LIBRARIES} pthread)

