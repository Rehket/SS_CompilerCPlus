cmake_minimum_required(VERSION 3.7)
project(SS_CompilerC__)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp LexicalAnalyzer.h VNM.h VNM.cpp)
add_executable(SS_CompilerC__ ${SOURCE_FILES})