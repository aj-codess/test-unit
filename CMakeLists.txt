cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_TOOLCHAIN_FILE /home/frank/Documents/Berita/server/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(testing_unit VERSION 1.0)

add_executable(main main.cpp)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dir)
