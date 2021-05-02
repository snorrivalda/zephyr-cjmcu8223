cmake_minimum_required(VERSION 3.13.1)

list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
# set(BOARD cjmcu8223)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(cjmcu8223_sample)

target_sources(app PRIVATE src/main.c)
