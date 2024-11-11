cmake_minimum_required(VERSION 3.0)
project(Houghlines_test)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    include
)

add_executable(Houghlines_test src/Houghlines_test.cpp)
target_link_libraries(Houghlines_test ${OpenCV_LIBS})
