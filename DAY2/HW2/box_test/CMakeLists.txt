cmake_minimum_required(VERSION 3.0)
project(box_test)

find_package(OpenCV REQUIRED)


add_executable(box_test src/box_test.cpp)
target_link_libraries(box_test ${OpenCV_LIBS})
