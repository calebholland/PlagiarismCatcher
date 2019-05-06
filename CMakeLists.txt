cmake_minimum_required(VERSION 3.14)
project(Cheaters)

set(CMAKE_CXX_STANDARD 11)

add_executable(Cheaters main.cpp getFileNames.cpp getFileNames.h plagiarismCatcher.cpp plagiarismCatcher.h FileChunks.cpp FileChunks.h Output.cpp Output.h)

