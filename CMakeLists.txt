cmake_minimum_required(VERSION 3.10)
project(sapi-tts)

set(CMAKE_CXX_STANDARD 17)

add_library(tts_lib utf8.cc tts.cc lib.cc)

add_executable(demo demo.cc)
target_link_libraries(demo tts_lib)
