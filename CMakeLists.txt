cmake_minimum_required(VERSION 3.27)
project(Image_to_ASCII)

set(CMAKE_CXX_STANDARD 20)

add_executable(Image_to_ASCII main.cpp)

find_package(CImg CONFIG REQUIRED)
target_link_libraries(Image_to_ASCII PRIVATE CImg::CImg)