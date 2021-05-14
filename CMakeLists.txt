cmake_minimum_required(VERSION 3.0)
project(XEnDec_test)

set(CMAKE_C_FLAGS "-g -fsanitize=address")

add_library(xemod_common STATIC xemod_common.c)
add_library(filend STATIC filend.c)

add_library(xemod1 STATIC xemod1.c)
add_library(xemod2 STATIC xemod2.c)
add_library(xemod3 STATIC xemod3.c)
add_library(xemod4 STATIC xemod4.c)
add_library(xemod5 STATIC xemod5.c)

add_executable(XEnDec_O3.out XEnDec_O3.c)
target_link_libraries(XEnDec_O3.out xemod3 xemod_common filend)

add_executable(XEnDec_O4.out XEnDec_O4.c)
target_link_libraries(XEnDec_O4.out xemod4 xemod_common filend)

add_executable(XEnDec_O5.out XEnDec_O5.c)
target_link_libraries(XEnDec_O5.out xemod5 xemod_common filend)

add_executable(XEnDec_V5-2.out XEnDec_V5-2.c)
target_link_libraries(XEnDec_V5-2.out xemod1 xemod2 xemod3 xemod4 xemod5 xemod_common filend)