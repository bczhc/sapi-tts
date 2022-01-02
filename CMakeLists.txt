cmake_minimum_required(VERSION 3.10)
project(sapi-tts C)

set(CMAKE_C_STANDARD 17)

add_library(lib utf8.c array_list.c tts.c lib.c)

add_executable(main main.c)
target_link_libraries(main lib)

add_executable(demo demo.c)
target_link_libraries(demo lib)
