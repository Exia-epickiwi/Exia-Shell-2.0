cmake_minimum_required(VERSION 3.4)
project(Exia-Shell-2.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c assistant.c cd.c config.c display.c exec.c expert.c hanoi.c language.c listUser.c log.c motd.c natural.c wcat.c wls.c wmount.c wpwd.c)
add_executable(exsh ${SOURCE_FILES})