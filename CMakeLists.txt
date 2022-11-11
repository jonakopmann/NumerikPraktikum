cmake_minimum_required(VERSION 3.12)

project(NumerikPraktikum
        VERSION 1.0.0)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

set(CMAKE_CXX_STANDARD 17)

set(main_files src/Main.cpp src/Process.cpp src/Polynom.cpp src/IO/Reader.cpp src/IO/Writer.cpp)

add_executable(Main ${main_files})

target_include_directories(Main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
