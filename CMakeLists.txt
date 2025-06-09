cmake_minimum_required(VERSION 4.0)

project(converter)


set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../compile)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ../compile/Debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  tinyxml2
  GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
  GIT_TAG        11.0.0
)
FetchContent_MakeAvailable(tinyxml2)

add_executable(converter
    source/main.cpp
)

target_compile_features(converter PRIVATE cxx_std_17)
target_link_libraries(converter PRIVATE tinyxml2)
