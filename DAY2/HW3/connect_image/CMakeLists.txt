cmake_minimum_required(VERSION 3.0)
project(connect_image)

find_package(OpenCV REQUIRED)


add_executable(connect_image src/connect_image.cpp)
target_link_libraries(connect_image ${OpenCV_LIBS})
