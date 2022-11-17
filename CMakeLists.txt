cmake_minimum_required(VERSION 3.12)

project(NumerikPraktikum
        VERSION 1.0.0)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

set(CMAKE_CXX_STANDARD 17)

set(main_files src/Main.cpp src/Process.cpp src/Polynom.cpp src/Utils.cpp src/IO/Reader.cpp src/IO/Writer.cpp)
set(test_files src/test.cpp src/Process.cpp src/Polynom.cpp src/Utils.cpp src/IO/Reader.cpp src/IO/Writer.cpp)

add_executable(Main ${main_files})
add_executable(Test ${test_files})

target_include_directories(Main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
