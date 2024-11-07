cmake_minimum_required(VERSION 3.0)
project(arm_opencv)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    include
)

add_executable(arm_opencv src/arm_opencv.cpp)
target_link_libraries(arm_opencv ${OpenCV_LIBS})
