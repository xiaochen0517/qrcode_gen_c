cmake_minimum_required(VERSION 3.28)
project(qrcode_gen_c C)

set(CMAKE_C_STANDARD 11)

# 使用 library/raylib 包
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/library/raylib/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/library/raylib/lib
)

add_executable(qrcode_gen_c src/main.c)

target_link_libraries(qrcode_gen_c raylib)
