cmake_minimum_required(VERSION 3.10)
project(ustrings C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2")

add_executable(ustrings ustrings.c)

install(TARGETS ustrings DESTINATION bin)
install(FILES README.md DESTINATION share/doc/ustrings)
