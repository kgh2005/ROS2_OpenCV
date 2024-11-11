cmake_minimum_required(VERSION 3.0)
project(contours_test)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    include
)

add_executable(contours_test src/contours_test.cpp)
target_link_libraries(contours_test ${OpenCV_LIBS})
