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

#target_include_directories(main_lib PRIVATE ./include/includes /home/koren/Desktop/gattlib-master/include)
#include_directories("{$CMAKE_SOURCE_DIR}/include/includes /home/koren/Desktop/gattlib-master/include")

#find_library(libgattlib gattlib "./include/lib")

#add_library(libgattlib SHARED IMPORTED)
#set_target_properties(libgattlib PROPERTIES IMPORTED_LOCATION include/lib/libgattlib.so)

set(SOURCE_FILES src/main.c src/data.c src/cli.c src/blescan.c)
include_directories(${PROJECT_SOURCE_DIR}/include)
#set(HEADER_FILES include/blescan.h include/cli.h include/data.h)
add_executable(Beaglebone ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(Beaglebone
        gattlib)
