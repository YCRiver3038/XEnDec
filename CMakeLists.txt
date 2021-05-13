cmake_minimum_required(VERSION 3.0)
project(XEnDec_test)

add_library(xemod_common STATIC xemod_common.c)
add_library(filend STATIC filend.c)

add_library(xemod3 STATIC xemod3.c)
add_library(xemod4 STATIC xemod4.c)
add_library(xemod5 STATIC xemod5.c)

add_executable(XEnDec_O3.out XEnDec_O3.c)
target_link_libraries(XEnDec_O3.out xemod3 xemod_common filend)

add_executable(XEnDec_O4.out XEnDec_O4.c)
target_link_libraries(XEnDec_O4.out xemod4 xemod_common filend)

add_executable(XEnDec_O5.out XEnDec_O5.c)
target_link_libraries(XEnDec_O5.out xemod5 xemod_common filend)